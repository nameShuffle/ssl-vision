#pragma once

#include <QThread>
#include <VarTypes.h>
#include <camera_calibration.h>
#include <camera_intrinsic_calib_widget.h>
#include <camera_parameters.h>
#include <framedata.h>
#include <image.h>
#include <memory>
#include <mutex>
#include <opencv2/opencv.hpp>
#include <visionplugin.h>

class Chessboard {
public:
  std::vector<cv::Point2f> corners;
  cv::Size pattern_size;
  bool pattern_was_found;
};

class ImageStorage : public QObject {
  Q_OBJECT
public:
  explicit ImageStorage(CameraIntrinsicCalibrationWidget *widget);
  ~ImageStorage() override;
  QThread *thread;
  CameraIntrinsicCalibrationWidget *widget;

  std::mutex image_save_mutex;
  std::queue<RawImage> images_to_save;

  VarString *image_dir;

  void saveImage(RawImage &image);
  void readImages(std::vector<cv::Mat> &images);

public slots:
  void saveImages();

signals:
  void startSaveImages();
};

class PluginCameraIntrinsicCalibrationWorker : public QObject {
  Q_OBJECT
public:
  explicit PluginCameraIntrinsicCalibrationWorker(
      CameraParameters &_camera_params,
      CameraIntrinsicCalibrationWidget *widget);
  ~PluginCameraIntrinsicCalibrationWorker() override;
  QThread *thread;
  std::mutex calib_mutex;

  CameraIntrinsicCalibrationWidget *widget;
  ImageStorage *image_storage;

  std::vector<std::vector<cv::Point3f>> object_points;
  std::vector<std::vector<cv::Point2f>> image_points;
  cv::Size imageSize;

  VarInt *corner_sub_pixel_windows_size;
  VarInt *corner_sub_pixel_max_iterations;
  VarDouble *corner_sub_pixel_epsilon;

  void detectChessboard(const cv::Mat &greyscale_mat, double scale_factor,
                        Chessboard *chessboard);
  bool findPattern(const cv::Mat &image, const cv::Size &pattern_size,
                   vector<cv::Point2f> &corners);

  void addChessboard(const Chessboard *chessboard);

  void clearData();

public slots:
  void loadImages();
  void calibrate();

signals:
  void startLoadImages();
  void startCalibration();

private:
  CameraParameters camera_params;
};

class PluginCameraIntrinsicCalibration : public VisionPlugin {
protected:
  std::unique_ptr<VarList> settings;

public:
  PluginCameraIntrinsicCalibration(FrameBuffer *_buffer,
                                   CameraParameters &camera_params);
  ~PluginCameraIntrinsicCalibration() override;

  QWidget *getControlWidget() override;

  ProcessResult process(FrameData *data, RenderOptions *options) override;
  VarList *getSettings() override;
  std::string getName() override;

private:
  PluginCameraIntrinsicCalibrationWorker *worker;

  CameraIntrinsicCalibrationWidget *widget;
  CameraParameters camera_params;

  VarDouble *scale_down_factor;
  VarDouble *chessboard_capture_dt;

  double lastChessboardCaptureFrame = 0.0;
};
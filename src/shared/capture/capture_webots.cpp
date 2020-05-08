//========================================================================
//  This software is free: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License Version 3,
//  as published by the Free Software Foundation.
//
//  This software is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  Version 3 in the file COPYING that came with this distribution.
//  If not, see <http://www.gnu.org/licenses/>.
//========================================================================
/*!
  \file    capturefromfile.cpp
  \brief   C++ Implementation: CaptureFromFile
  \author  OB, (C) 2008
  \author  TL, (C) 2009
*/
//========================================================================

#include <sys/time.h>
#include <cctype>
#include "capture_webots.h"
#include "image_io.h"
#include "conversions.h"
#include <sstream>
#include <fstream>
#include <opencv2/opencv.hpp>

#include <QImage>
#include <QString>


Client::Client(const QString& strHost, int port, std::queue<RawImage>* images, QMutex* mutex, bool* capturingStatus)
{
    socket = new QTcpSocket(this);
    captureMutex = mutex;
    rowImages = images;
    isCapturing = capturingStatus;

    nextImageColumns = 0;
    nextImageRows = 0;
    nextImageSize = 0;

    socket->connectToHost(strHost, port);

    connect(socket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(socket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(slotError(QAbstractSocket::SocketError))
           );;
}


void Client::slotReadyRead()
{
    captureMutex->lock();

    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_4_2);
    in.setByteOrder(QDataStream::LittleEndian);

    for (;;) {
        if (!nextImageSize) {
            if (socket->bytesAvailable() < sizeof(uint)) {
                break;
            }

            if (!nextImageColumns)
            {
                in >> nextImageColumns;
                break;
            }
            else if (!nextImageRows)
            {
                in >> nextImageRows;
                nextImageSize = nextImageColumns * nextImageRows * 4;
            }
        }

        if (socket->bytesAvailable() < nextImageSize) {
            break;
        }

        char* imageBytes = new char [nextImageSize];
        in.readRawData(imageBytes, nextImageSize);

        cv::Mat srcImg = cv::Mat(nextImageRows, nextImageColumns, CV_8UC4,
                           const_cast<uchar*>((uchar*)imageBytes), nextImageColumns * 4);


        RawImage img;
        img.allocate(ColorFormat::COLOR_RGB8, srcImg.cols, srcImg.rows);

        cv::Mat dstImg(img.getHeight(), img.getWidth(), CV_8UC3, img.getData());

        // convert to default ssl-vision format (RGB8)
        cvtColor(srcImg, dstImg, CV_BGRA2RGB);

        rowImages->push(img);

        nextImageSize = 0;
        nextImageRows = 0;
        nextImageColumns = 0;
    }

    *isCapturing = true;
    captureMutex->unlock();
}


void Client::slotError(QAbstractSocket::SocketError err)
{
    QString strError =
        "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                     "The host was not found." :
                     err == QAbstractSocket::RemoteHostClosedError ?
                     "The remote host is closed." :
                     err == QAbstractSocket::ConnectionRefusedError ?
                     "The connection was refused." :
                     QString(socket->errorString())
                    );

    fprintf(stderr, strError.toStdString().c_str());
}


void Client::slotConnected()
{
    fprintf(stderr, "Received the connected() signal");
}


void Client::stopListening()
{
    socket->close();
}


CaptureWebots::CaptureWebots(VarList * _settings, int default_camera_id,
                             QObject * parent) : QObject(parent), CaptureInterface(_settings)
{
    is_capturing = false;

    settings->addChild(conversion_settings = new VarList("Conversion Settings"));
    settings->addChild(capture_settings = new VarList("Capture Settings"));

    //=======================CONVERSION SETTINGS=======================
    conversion_settings->addChild(v_colorout = new VarStringEnum(
              "convert to mode", Colors::colorFormatToString(COLOR_YUV422_UYVY)));

    v_colorout->addItem(Colors::colorFormatToString(COLOR_RGB8));
    v_colorout->addItem(Colors::colorFormatToString(COLOR_YUV422_UYVY));
    v_colorout->addItem(Colors::colorFormatToString(COLOR_RAW8));

    //=======================CAPTURE SETTINGS==========================
    ostringstream convert;
    convert << "test-data/cam" << default_camera_id;
    capture_settings->addChild(webots_address = new VarString("address", "192.168.0.16"));
    capture_settings->addChild(webots_port = new VarInt("port", 7777));
}

CaptureWebots::~CaptureWebots()
{
}


bool CaptureWebots::stopCapture()
{
    cleanup();

    return true;
}


void CaptureWebots::cleanup()
{
    mutex.lock();

    is_capturing = false;
    client->stopListening();

    mutex.unlock();
}


bool CaptureWebots::startCapture()
{
    mutex.lock();

    client = new Client (QString::fromStdString(webots_address->getString()), webots_port->getInt(), &images, &mutex, &is_capturing);

    mutex.unlock();

    return true;
}


bool CaptureWebots::copyAndConvertFrame(const RawImage & src, RawImage & target)
{
    mutex.lock();

    ColorFormat output_fmt = Colors::stringToColorFormat(v_colorout->getSelection().c_str());
    ColorFormat src_fmt = src.getColorFormat();

    target.ensure_allocation(output_fmt, src.getWidth(), src.getHeight());
    target.setTime(src.getTime());

    if (output_fmt == src_fmt)
    {
        memcpy(target.getData(), src.getData(), static_cast<size_t>(src.getNumBytes()));
    }
    else if(src_fmt == COLOR_RAW8 && output_fmt == COLOR_RGB8)
    {
        cv::Mat srcMat(src.getHeight(), src.getWidth(), CV_8UC1, src.getData());
        cv::Mat dstMat(target.getHeight(), target.getWidth(), CV_8UC3, target.getData());
        cvtColor(srcMat, dstMat, cv::COLOR_BayerRG2BGR);
    }
#ifndef NO_DC1394_CONVERSIONS
    else if(src_fmt == COLOR_RAW8 && output_fmt == COLOR_YUV422_UYVY)
    {
        // note: this an inefficient double conversion and should only be used for testing!
        cv::Mat srcMat(src.getHeight(), src.getWidth(), CV_8UC1, src.getData());
        cv::Mat dstMat(target.getHeight(), target.getWidth(), CV_8UC3);
        cvtColor(srcMat, dstMat, cv::COLOR_BayerRG2BGR);
        dc1394_convert_to_YUV422(dstMat.data, target.getData(), src.getWidth(), src.getHeight(),
                                 DC1394_BYTE_ORDER_UYVY, DC1394_COLOR_CODING_RGB8, 8);
    }
    else if (src_fmt == COLOR_RGB8 && output_fmt == COLOR_YUV422_UYVY)
    {
        if (src.getData() != 0)
            dc1394_convert_to_YUV422(src.getData(), target.getData(), src.getWidth(), src.getHeight(),
                                    DC1394_BYTE_ORDER_UYVY, DC1394_COLOR_CODING_RGB8, 8);
    }
    else if (src_fmt == COLOR_YUV422_UYVY && output_fmt == COLOR_RGB8)
    {
        if (src.getData() != 0)
            dc1394_convert_to_RGB8(src.getData(), target.getData(), src.getWidth(), src.getHeight(),
                                     DC1394_BYTE_ORDER_UYVY, DC1394_COLOR_CODING_YUV422, 8);
    }
#endif
    else
    {
        fprintf(stderr, "Cannot copy and convert frame...unknown conversion selected from: %s to %s\n",
        Colors::colorFormatToString(src_fmt).c_str(),
        Colors::colorFormatToString(output_fmt).c_str());

        mutex.unlock();
        return false;
    }

    mutex.unlock();
    return true;
}


RawImage CaptureWebots::getFrame()
{
    mutex.lock();

    RawImage result;
    if (images.empty())
    {
        fprintf (stderr, "CaptureWebots Error, no images available yet");
        is_capturing = false;

        result.setData(nullptr);
        result.setWidth(640);
        result.setHeight(480);
        result.setTime(0.0);
    }
    else
    {
        result = images.front();
        images.pop();

        timeval tv{};
        gettimeofday(&tv, nullptr);
        result.setTime((double) tv.tv_sec + tv.tv_usec*(1.0E-6));
    }

    mutex.unlock();
    return result;
}

void CaptureWebots::releaseFrame()
{
    mutex.lock();
    mutex.unlock();
}

string CaptureWebots::getCaptureMethodName() const
{
    return "WebotsMode";
}

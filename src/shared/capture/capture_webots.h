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
  \file    capturefromfile.h
  \brief   C++ Interface: CaptureFromFile
  \author  OB, (C) 2009
  \author  TL, (C) 2009
*/
//========================================================================

#ifndef CAPTURE_WEBOTS_H
#define CAPTURE_WEBOTS_H

#include "captureinterface.h"
#include <dirent.h>
#include <string>
#include <list>
#include <algorithm>
#include "VarTypes.h"

#include <QTcpSocket>
#include <QMutex>
#include <QWidget>


class Client : public QWidget{
Q_OBJECT

private:
    QTcpSocket* socket;
    std::queue<RawImage>* rowImages;
    QMutex *captureMutex;
    bool *isCapturing;
    uint       nextImageSize;
    uint       nextImageColumns;
    uint       nextImageRows;

public:
    Client(const QString& strHost, int port, std::queue<RawImage>* images, QMutex* mutex, bool* isCapturing) ;
    void stopListening();

private slots:
    void slotReadyRead   (                            );
    void slotError       (QAbstractSocket::SocketError);
    void slotConnected   (                            );
};


class CaptureWebots : public QObject, public CaptureInterface
{
    Q_OBJECT

    protected:
        QMutex mutex;

    protected:
        bool is_capturing;

        //processing variables:
        VarStringEnum * v_colorout;

        //capture variables:
        VarString* webots_address;
        VarInt* webots_port;

        VarList* capture_settings;
        VarList* conversion_settings;

        std::queue<RawImage> images;

        Client* client = nullptr;

    public:
        CaptureWebots(VarList * _settings, int default_camera_id, QObject * parent=0);
        void mvc_connect(VarList * group);
        ~CaptureWebots();

        virtual bool startCapture();
        virtual bool stopCapture();
        virtual bool isCapturing() { return is_capturing; }

        virtual RawImage getFrame();
        virtual void releaseFrame();

        void cleanup();

        virtual bool copyAndConvertFrame(const RawImage & src, RawImage & target);
        virtual string getCaptureMethodName() const;
};

#endif

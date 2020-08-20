/***************************************************************************
 * Copyright (C) 2020 by EWT                                               *
 *                                                                         *
 * All Rights Reserved.                                                    *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 * Author: Erik Miers                                                      *
 * Email: erik.miers@gmail.com                                             *
 ***************************************************************************/

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QSurfaceFormat>

#include "granuleitemmodel.h"
#include "constants.h"


int main(int argc, char *argv[])
{
	{
		// Set OpenGL requirements
		QSurfaceFormat format = QSurfaceFormat::defaultFormat();
#ifndef QT_OPENGL_ES_2
		format.setVersion(4, 1);
		format.setProfile(QSurfaceFormat::CoreProfile);
		format.setSamples(4);
#else
		format.setVersion(3, 0);
		format.setProfile(QSurfaceFormat::NoProfile);
		format.setRenderableType(QSurfaceFormat::OpenGLES);
#endif
		QSurfaceFormat::setDefaultFormat(format);
	}

	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	QGuiApplication app(argc, argv);


	qmlRegisterSingletonType<Universe::Constants> ("ewt.sim", 1, 0, "Constants",
	        [](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject * {
		Q_UNUSED(engine)
		Q_UNUSED(scriptEngine)

		return &Universe::Constants::instance();
	});
	QQmlEngine::setObjectOwnership(&Universe::Constants::instance(), QQmlEngine::CppOwnership);

	qmlRegisterType<SpaceTime::GranuleItemModel>("ewt.sim", 1, 0, "GranuleItemModel");

	QQuickView view;

	view.resize(1024, 768);
	view.setResizeMode(QQuickView::SizeRootObjectToView);
	view.setSource(QUrl("qrc:/main.qml"));
	view.show();

	return app.exec();
}


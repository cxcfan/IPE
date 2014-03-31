IPE
======================

Introduction
----------------------
IPE is a project for processing digital images. It origins from a project in course. We are adding more features and improving its performance now.

Configuration
----------------------
**1.**Requirement: Visual Studio 2012, Qt5 and Qt Addin for VS2012.

**2.**Config environment variables on Windows

		$(LIB)={path for external libraries}
		$(QTDIR)={path of Qt installation (e.g. C:\Qt\Qt5.2.1\5.2.1\msvc2012_64_opengl)}
		$(PATH)={path of binaries of libraries (e.g. C:\Qt\Qt5.2.1\5.2.1\msvc2012_64_opengl\bin)}

**3.**Install external libraries on `$(LIB)`.
  
[`GLEW`](http://glew.sourceforge.net): The OpenGL Extension Wrangler Library

[`OpenGL Mathematics(GLM)`](http://sourceforge.net/projects/ogl-math): The OpenGL Mathematics Library

[`OpenCV`](http://opencv.org): Open Source Computer Vision Library

Installation instructions for GLEW: http://glew.sourceforge.net/install.html

**4.**Open the project and change Qt version. If your OpenCV version is not 2.4.8, change additional dependencies in Visual Studio because filenames of OpenCV DLLs are related to version.

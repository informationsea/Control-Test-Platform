#ifndef _README_H_
#define _README_H_

#warning "You don't have to include readme.h"

/**
   @file readme.h
   @author Y.Okamura
   
   \mainpage
   I developed this library for robot control practice.
   You can try PID control or other control theory easily with this library.
   In this library, some robots and fields are prepared.
   You just have to combine those objects to use this.

   \section how_to_compile How to compile

   \subsection for_windows For Windows

   Sorry, Windows is not supported yet.
   
   \subsection for_unix Mac OS X and Linux

   First, you have to install build tools. If you are using ubuntu, try below commands.
\verbatim
sudo apt-get install xorg-dev freeglut3-dev
\endverbatim
   If you are using Mac OS X, please install Xcode from AppStore or Mac Developer Center.

   Next, you have to install Open Dynamics Engine. Don't install by apt-get or port.
   You have to apply patch to install drawstuff.

  
\verbatim
cd ode-1.2
patch -p1 < ../Control-Test-Platform/misc/ode-1.2.patch
./configure --enable-double-precision
make
sudo make install
\endverbatim

   Finally, install Control Test Platform.

\verbatim
cd Control-Test-Platform
./configure
make
sudo make install
\endverbatim


\section basic_usage Basic Usage

\include roller-robot/slope_roller.h
\include roller-robot/slope_roller.cpp
\include roller-robot/onoff_controller.c
   
 */

/**
 *  @defgroup ode Open Dynamics Engine
 */

/** @defgroup world
 *  @ingroup ode
 */

/** @defgroup bodies
 *  @ingroup ode
 */

/** @defgroup joints
 *  @ingroup ode
 */

/** @defgroup collide
 *  @ingroup ode
 */

/** @defgroup init
 *  @ingroup ode
 */

/** @defgroup drawstuff
 *  @ingroup ode
 */

/**
 *  @defgroup disable
 *  @ingroup world bodies
 */

/**
 *  @defgroup damping
 *  @ingroup world bodies
 */

/**
 * @defgroup collide_sphere
 * @ingroup collide
 */

/**
 * @defgroup collide_box
 * @ingroup collide
 */


#endif /* _README_H_ */

#ifndef _README_H_
#define _README_H_

#warning "You don't have to include readme.h"

/**
   @file readme.h
   @author Y.Okamura
   
   \mainpage
   このライブラリは Open Dynamics Engine を用いたロボットのシミュレーションを簡単に行うためのライブラリです。あらかじめ、いくつかのロボットの型とフィールドが登録されており、それらを組み合わせるだけで、簡単に制御の練習が出来ます。新たにフィールドやロボットを追加すれば、それと既存のフィールドなどを組み合わせることも簡単にできます。

   \section how_to_compile コンパイル方法について
   あらかじめ Open Dynamics Engine のコンパイルが必要になります。ODE付属のDrawstuff も必要になりますので Mac Ports などのパッケージシステムを用いてインストールしないでください。必ず手動でDrawstuffを含めてインストールしてください。

   \subsection for_windows Windows の場合
   Windows では MinGW ( http://www.mingw.org/ ) を用いてコンパイルします。MinGWのインストール時にはC++とMinGW Developer Kitのインストールをお忘れなく。MinGWのホームディレクトリにODEのソースを展開します。ここではODE 0.11.1を前提としています。MinGW Shellを開き、ode-0.11.1/buildに移動しましょう。その上で次のコマンドを実行してください。

\verbatim
premake4.exe --with-demos gmake
cd gmake
make config=releasedoublelib CC=gcc
\endverbatim

上手く行ったら次のコマンドで正しく動くことを確認しましょう。

\verbatim
cd ../../lib/ReleaseDoubleLib/
demo_crash.exe
\endverbatim

これでODEのインストールがおしまいです。次にControl Test Platformのビルドに移ります。次のようにファイルを配置してください。

\verbatim
SomeDir + ode-0.11.1 + ...
        |
        + control-test-platform + ...
\endverbatim

次にMinGW Shellでcontrol-test-platformの中に移動します。そこで次のコマンドを実行してください

\verbatim
source environment.sh
\endverbatim

これによって必要な環境変数を設定します。これは毎回実行せねばなりません。あとは、compile.shを実行すれば、まとめてコンパイルされますし、個別にmakeを実行しても
コンパイルできます。

\subsection for_unix Mac OS X および Linux の場合
  Linuxの場合はビルドに必要なパッケージをインストールしておきましょう。
X Window Systemの開発パッケージとGlUTの開発パッケージがあれば十分です。Ubuntu
であれば

\verbatim
sudo apt-get install xorg-dev freeglut3-dev
\endverbatim
とすればインストールできます。

  まずはconfigureしましょう。Linuxなら
\verbatim
./configure --enable-double-precision
\endverbatim
Mac OS Xなら
\verbatim
CPPFLAGS='-m32 -O3 -mtune=native' LDFLAGS='-m32' ./configure --enable-double-precision
\endverbatim
としましょう。Mac OS Xでは64 bitではコンパイルできないのでこのようにする必要があります。configureがとおれば
\verbatim
make
\endverbatim
でコンパイルします。-jオプションで並列数を指定すれば早いかもしれません。
インストールには次のようにします。以下のコマンドはsudoをつけて実行しましょう。
\verbatim
make install
cp drawstuff/src/.libs/libdrawstuff.* /usr/local/lib/
mkdir /usr/local/include/drawstuff
cp include/drawstuff/*.h /usr/local/include/drawstuff/
mkdir -p /usr/local/share/drawstuff
cp drawstuff/textures/*.ppm /usr/local/share/drawstuff/
\endverbatim

Drawstuffは個別にインストールするひつようがあるのでこのようになっています。
あとは、control-test-platformの中でcompile.shを実行すれば、まとめてコンパイルされますし、個別にmakeを実行してもコンパイルできます。

\section basic_usage 基本的な使い方

\include ../nhk-normal/main/nhk_normal.cpp
\include ../nhk-normal/key-control/controller.c

基本的には上のソースコードに示した通りです。まずは
\code
platform_initialize();
\endcode
を呼んで環境を初期化した後に、
\code
platform_add_objectset(new NormalRobot());
platform_add_objectset(new NHK2012Field());
\endcode
のように使いたいオブジェクトを追加していきます。ここでは ObjectSet のサブクラスが追加できるので、使いたいものを追加してください。最後に
\code
platform_start(argc, argv);
\endcode
でシミュレーションをスタートできます。シミュレーションをスタートすると、次の四つの関数が適宜呼び出されます。これらの関数はユーザーが実装する必要があります。
\code
// 制御プログラムの初期化　このときにはすべてのオブジェクトにアクセス可
void controller_initialize(void);

// シミュレーションの1ステップごとに呼び出される。1ステップはSTEP_SIZE秒
void controller_simulation_step(void);

// キーが押されたときに呼び出される。
void controller_key_event(int key);

// 制御プログラムの終了処理。
void controller_finalize(void);
\endcode
この中からロボットを制御します。どのように制御するかはそれぞれの ObjectSet のサブクラスごとに違いますので、そちらを参照してください。

\section objectset ObjectSet

Control Test Platformではロボットやフィールドを ObjectSet という集合で扱います。 ObjectSet には今のところ RollerRobot, NormalRobot, NHK2012Field, InRoFField があります。ここでは簡単な説明にとどめますので、詳細は各ヘッダファイルを覗いてださい。

\subsection nhk2012field NHK2012Field

   - nhk2012field.h
   - nhk2012field.cpp

   名前の通りです。設定項目はありません。

\subsection inroffield InRoFField

   - inroffield.h
   - inroffield.cpp

   名前の通りです。設定項目はありません。

\subsection normalrobot NormalRobot

   - normal.h
   - normal.cpp

     動輪二つにボールキャスターの普通のロボットです。パラメータにより、サイズや初期位置を変更できます。C言語からユーザーが使用可能な関数は以下の通りです。それぞれの関数は最後に作られたNormalRobotを操作します。

\code
// ロボットの位置を返します。
struct CarPoint car_get_position(void);

// 左側のモーターのトルクを設定します
void car_set_motor_torque_left(double torque);

// 右側のモーターのトルクを設定します
void car_set_motor_torque_right(double torque);

// エンコーダーの値を取得します
void car_get_encoder_value(double *left, double *right);
\endcode

\subsection rollerrobot RollerRobot

   - roller.h
   - roller.cpp

     前後方向にのみ動けるロボットです。一次元の制御の練習用です。
     C言語からユーザーが使用可能な関数は以下の通りです。
     それぞれの関数は最後に作られたRollerRobotを操作します。

\code
// ロボットのX座標を返します。
double roller_get_point(void);

// モーターのトルクを設定します。
void roller_set_motor_torque(double torque);

// エンコーダーの値を返します
double roller_get_encoder_value();
\endcode


   
 */

/** @defgroup ode Open Dynamics Engine
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

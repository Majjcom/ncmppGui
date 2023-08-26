#include "getpath.h"

#include <QtCore>

#ifdef Q_OS_ANDROID
#include <QAndroidJniObject>
QString get_home_path()
{
    QAndroidJniObject environment = QAndroidJniObject::callStaticObjectMethod(
        "android/os/Environment", "getExternalStorageDirectory", "()Ljava/io/File;"
    );

    QAndroidJniObject path = environment.callObjectMethod("getPath", "()Ljava/lang/String;");

    QString storagePath = path.toString();

    return storagePath;
}
#else
QString get_home_path()
{
    return QDir::homePath();
}
#endif


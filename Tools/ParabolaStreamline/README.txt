################################################################
# Parabola Engine SDK Streamline Tool - ps (Parabola Streamline)
################################################################

The streamline tool is provided merely as an assistant for common tasks in game development.
It is a part of the SDK, but not an essential part of it.

You may use this tool for tasks such as:



------------------------------------------------------------------------------------------------------------------------------------------------------
-> Creating an Android APK
:: It would be possible to make a fully C++ android application, but that doesn't help in compatibility or flexibility.
:: Therefore, the SDK only works with Java applications interfacing with the engine code. You don't need to touch anything in Java using this tool.

In its simplest form, you can generate the APK file structure you will need to deploy in Android with the following command:
ps gen-apk com.engine.demo

It will create a directory named APK in the ps directory, with all the needed contents, in their default form.
If you want to output to another directory, please add the option -oMyDir or -oC:\MyDir.

While the module gen-apk is in its baby steps, you may only workout the default settings for the application with the tokens it knows about.

You can override any token with your own content. To do so, use ps gen-apk com.engine.demo -tTOKEN_NAME=RESULT.
This is not very flexible yet, but will be improved, anyway here are some token names:

PROJECT_PROPERTIES_ANDROID_API
ANDROID_MANIFEST_AIRPUSH_HOLDER
PACKAGE_VERSION
ANDROID_MANIFEST_ICON_DEFINITION
ANDROID_MANIFEST_ACTIVITY_ORIENTATION
ANDROID_MANIFEST_MINSDK
PROJECT_NAME
ACTIVITY_LABEL
APPLICATION_LABEL
ACTIVITY_CLASS
AIRPUSH_APPID
AIRPUSH_APIKEY
AIRPUSH_TESTMODE
AIRPUSH_PUSHADS
AIRPUSH_ICONADS
AIRPUSH_IMPORT
ACTIVITY_FEATURE_SENDSMS

Please investigate the source of the tool and the APKModel files in the resources directory. Otherwise contact me at artturmoreira@gmail.com

For more info, check the help in the ps tool.
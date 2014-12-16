#include <moai-android-twitter/host.h>
#include <jni.h>
#include <moai-android/JniUtils.h>
#ifndef DISABLE_TWITTER
extern "C" void Java_com_ziplinegames_moai_MoaiTwitter_AKUNotifyTwitterLoginComplete ( JNIEnv* env, jclass obj,
                                                                    jint code, jstring jtoken, jstring jtokenSecret ) {

	JNI_GET_CSTRING ( jtoken, token );
	JNI_GET_CSTRING ( jtokenSecret, tokenSecret );

	AKUAndroidTwitterNotifyLoginComplete ( code, token, tokenSecret );

	JNI_RELEASE_CSTRING ( jtoken, token );
	JNI_RELEASE_CSTRING ( jtokenSecret, tokenSecret );
}

//----------------------------------------------------------------//
extern "C" void Java_com_ziplinegames_moai_MoaiTwitter_AKUNotifyTwitterTweetComplete ( JNIEnv* env, jclass obj, jint code ) {

	AKUAndroidTwitterNotifyTweetComplete ( code );

}
#endif
/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class quizserver_QuizServer */

#ifndef _Included_quizserver_QuizServer
#define _Included_quizserver_QuizServer
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     quizserver_QuizServer
 * Method:    initializesocket
 * Signature: (ILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_quizserver_QuizServer_initializesocket
  (JNIEnv *, jobject, jint, jstring);

/*
 * Class:     quizserver_QuizServer
 * Method:    makeConnection
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_quizserver_QuizServer_makeConnection
  (JNIEnv *, jobject);

/*
 * Class:     quizserver_QuizServer
 * Method:    buzzerRound
 * Signature: (III)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_quizserver_QuizServer_buzzerRound
  (JNIEnv *, jobject, jint, jint, jint);

/*
 * Class:     quizserver_QuizServer
 * Method:    passRound
 * Signature: (IIIII)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_quizserver_QuizServer_passRound
  (JNIEnv *, jobject, jint, jint, jint, jint, jint);

/*
 * Class:     quizserver_QuizServer
 * Method:    closeAll
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_quizserver_QuizServer_closeAll
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     quizserver_QuizServer
 * Method:    broadcastQuestion
 * Signature: ([Ljava/lang/String;II)V
 */
JNIEXPORT void JNICALL Java_quizserver_QuizServer_broadcastMessage
  (JNIEnv *, jobject, jobjectArray, jint, jint);

#ifdef __cplusplus
}
#endif
#endif

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>

using namespace std ;
using namespace cv ;

int main( )
{

	Mat image , grayImage ;
	VideoCapture cap( "D:\\cutebaby.mp4" ) ;

	String faceFilePath = "C:\\Program Files\\opencv\\data\\haarcascades\\haarcascade_frontalface_alt.xml" ;

	CascadeClassifier cascadeFace , cascadeEyes ;
	if( !cascadeFace.load( faceFilePath ) )
	{
		return -1 ;
	}

	if( !cap.isOpened( ) )
	{
		return -1 ;
	}

	int nowFrame = 1 ;													//Declaration a integer variable as 1st frame.
	int totalFrame = ( int )cap.get( CV_CAP_PROP_FRAME_COUNT ) ;		//Get the total frame number of the video.

	while( nowFrame ++ != totalFrame )
	{
		cap >> image ;
		cvtColor( image, grayImage, CV_BGR2GRAY );
		Mat equaImg ;
		equalizeHist( grayImage, equaImg );

		std :: vector< Rect > faces ;
		cascadeFace.detectMultiScale( equaImg , faces , 1.5 , 2 , CV_HAAR_SCALE_IMAGE , Size( 10 , 10 ) ) ;

		for( int i = 0 ; i < faces.size( ) ; i ++ )
		{
			Point center( faces[ i ].x + faces[ i ].width * 0.5 , faces[ i ].y + faces[ i ].height * 0.5 ) ;
			int radius = cvRound( ( faces[ i ].width+faces[ i ].height ) * 0.25 ) ;
			circle( image , center ,  radius , Scalar( 255, 0, 0 ) , 4 , 8 , 0 ) ;
		}
		imshow( "face" , image ) ;

		if( waitKey( 1 ) == 'q' )
		{
			break ;
		}
	}

	return 0;
}

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>

#include <vector>
#include <cstring>
#include <cstdlib>
#include <iostream>

using namespace cv;
using namespace std ;

int main( )
{
	vector< Mat > image ;
	vector< Mat > grayImg ;

	string file = "img_00" ;
	string fileType = ".jpg" ;
	for( int i = 0 ; i < 6 ; i ++ )
	{
		char buffer[ 10 ] ;
		string fileNumber = itoa( i + 1 , buffer , 10 ) ;
		string fileName = file + fileNumber + fileType ;

		Mat input = imread( fileName ) ;
		image.push_back( input ) ;

		Mat gray ;
		cvtColor( input , gray , CV_BGR2GRAY ) ;
		equalizeHist( gray , gray ) ;
		grayImg.push_back( gray ) ;
	}

	cout << "face detecting, please wait...\n" ;

	String faceFilePath = "D:\\User Programs\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml" ;
	String eyesFilePath = "D:\\User Programs\\opencv\\sources\\data\\haarcascades\\haarcascade_eye_tree_eyeglasses.xml" ;

	CascadeClassifier cascadeFace , cascadeEyes ;
	cascadeFace.load( faceFilePath ) ;
	cascadeEyes.load( eyesFilePath ) ;

	vector < Rect > *vecFaces = new vector< Rect >[ grayImg.size( ) ] ;


	cascadeFace.detectMultiScale( grayImg[ 0 ] , vecFaces[ 0 ] , 1.1 , 2 , 0 , Size( 50 ,50 ) ) ;		//image_001
	cascadeFace.detectMultiScale( grayImg[ 1 ] , vecFaces[ 1 ] , 1.02 , 4 , 3 , Size( 0.5 , 0.5 ) ) ;	//image_002
	cascadeFace.detectMultiScale( grayImg[ 2 ] , vecFaces[ 2 ] , 1.08 , 1.9 , 0 , Size( 5 ,5 ) ) ;		//image_003
	cascadeFace.detectMultiScale( grayImg[ 3 ] , vecFaces[ 3 ] , 1.041 , 4 , 1 , Size( 2 , 30 ) ) ;		//image_004
	cascadeFace.detectMultiScale( grayImg[ 4 ] , vecFaces[ 4 ] , 1.05 , 5 , 0 , Size( 5 , 5 ) ) ;		//image_005
	cascadeFace.detectMultiScale( grayImg[ 5 ] , vecFaces[ 5 ] , 1.1 , 2 , 0 , Size( 5 , 5 ) ) ;		//image_006

	int radius = 0 ;
	for( int i = 0 ; i < grayImg.size( ) ; i ++ )
	{
		for( int j = 0 ; j < vecFaces[ i ].size( ) ; j ++ )
		{
			Point center( vecFaces[ i ][ j ].x + vecFaces[ i ][ j ].width * 0.5 , vecFaces[ i ][ j ].y + vecFaces[ i ][ j ].height * 0.5 ) ;
			radius = cvRound( ( vecFaces[ i ][ j ].width+vecFaces[ i ][ j ].height ) * 0.25 ) ;
			circle( image[ i ] , center ,  radius , Scalar( 255, 0, 0 ) , 4 , 8 , 0 ) ;
		}
		char buffer[ 10 ] ;
		string name = itoa( i + 1 , buffer , 10 ) ;
		imshow( name , image[ i ] ) ;
		waitKey( 0 ) ;
	}

	return 0;
}

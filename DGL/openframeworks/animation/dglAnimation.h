#pragma once

#include "ofMain.h"

class dglAnimation
{
public:
	dglAnimation();

	//ֱ�Ӷ���һ����XXX�ļ��е�֡����ͼƬ(�ļ���λ��of���̵�bin/data��) ��-1��ʼֱ��-sumΪֹ
	//��Ҫ������ʽΪ"XXX-1.png/bmp..."�ȵ�
	//�ļ����� ��׺��(�����ļ��ĸ�ʽ����ҪͳһΪͬһ��ʽ) ֡��(�ļ�����)
	void loadFrames(string folderName, string suffixFormat, int sumNumber);

	//���֡����ͼ
	void addFrame(ofImage image);

	//��ָ��λ�û��Ƶ�ǰ֡
	void drawCurrentFrame(ofVec3f position);

	//֡����ͳһ���
	int width, height;

	//��ǰ֡
	int currentFrame;
	//��֡��
	int sumFrames;

	//֡������
	vector<ofImage> pictures;
};
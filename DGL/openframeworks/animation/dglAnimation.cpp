#include "dglAnimation.h"

dglAnimation::dglAnimation()
{
	currentFrame = 0;
	sumFrames = 0;

	//���������
	pictures.clear();
}

void dglAnimation::loadFrames(string folderName, string suffixFormat, int sumNumber)
{
	int sumWidth=0, sumHeight=0;

	ofImage temp;
	string current;
	char convert[5];

	//ѭ������������ļ���
	for(int i=1; i<=sumNumber; i++)
	{
		//��int��iת��Ϊchar*֮����ת��Ϊstring
		sprintf(convert, "%d", i);
		current = convert;
		//�ļ���/folderName-x.suffix
		if(!temp.loadImage(folderName + "/" + folderName + "-" + current + "." + suffixFormat))
		{
			printf("�޷���ָ���ļ����ж�ȡ֡�������ͼƬ");
			continue;
		}

		sumWidth += temp.getWidth();
		sumHeight += temp.getHeight();

		addFrame(temp);
	}

	//��ʼ��֡������ƽ�����
	width = sumWidth/sumNumber;
	height = sumHeight/sumNumber;
}

void dglAnimation::addFrame(ofImage image)
{
	//��β��������ͼƬ/֡
	pictures.push_back(image);

	sumFrames++;
}

void dglAnimation::drawCurrentFrame(ofVec3f position)
{
	//����ǰ����û��֡��ֱ������
	if(sumFrames == 0)
		return;

	//ͷβѭ�����µ�ǰ֡λ��ָ��
	currentFrame = (currentFrame+1) % sumFrames;

	//��ָ��λ��ֱ�ӻ��Ƴ�����ͼƬ�����֡����
	pictures[currentFrame].draw(position.x, position.y, position.z);
}
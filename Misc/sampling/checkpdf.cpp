float get_expected_value(const std::vector<float>& v)
{
	if(v.empty()) return 0;
	float sum = 0;
	for(int i=0;i<v.size();++i)
	{
		sum += v[i];
	}
	sum/=v.size();
	return sum;
}

float get_variance(const std::vector<float>& v)
{
	if(v.empty()) return 0;
	float sum = 0;
	float expected = get_expected_value(v);
	for(int i=0;i<v.size();++i)
	{
		float temp = (v[i] - expected);
		sum += temp*temp;
	}
	sum/=(v.size()-1);
	return sum;
}


float get_standard_deviation(const std::vector<float>& v)
{
	if(v.empty()) return 0;
	return sqrt(get_variance(v));
}

//����һ������ͳ��ͼ
void check(std::vector<float> v,NormalView* app,ofColor c=ofColor::black,float scale = 0.2)
{
	if(v.empty()) return;
	const int acc = 140;
	float a[acc]={0};
	for(int i=0;i<v.size();++i)
	{
		float t =0;
		int idx = 0;
		for(int j=0;j<acc;++j)
		{
			if(v[i]>=t&&v[i]<t+1.f/(float)acc) 
			{
				a[idx]++;
				break;
			}
			t +=1.f/acc;
			++idx;
		}
	}
	//��������[0,1],��
	//ԭ����Ƶ��ͼ����Ӧ�ý�dx����Ϊ1��������sum f(x)dx = 1
	//���ڣ����������ŵ�����Ϊ1������Ϊ�˱�֤����Ϊ1��Ӧ�ð�dx�޸�Ϊ��Ӧ�Ĵ�С������
	//sum c f(x) dx = 1
	//dx = 1/acc & sum f(x)=1 -> c = acc
	float intval = 1.f/acc;
	for(int i=0;i<acc;++i)
	{
		a[i] = (float)a[i]/v.size()*acc;
	}


	//���д������ͳ��ͼ
	/*
	��һ����app->grid_panel->get_res_w()��app->grid_panel->get_res_h()�������ڻ�ͼ
	scale�����ţ���֤�ͻ���pdf����ʱ������һ��
	+10��ƫ�뵥λ
	*/
	for(int i=0;i<acc;++i)
	{
		//�ܳ���
		int idx = (float)i/acc*app->grid_panel->get_res_w();
		app->grid_panel->set_px(idx,a[i]*app->grid_panel->get_res_h()*scale+10,c);
	}
}

//input normalized
void check2d(std::vector<ofVec2f>& v,GridCanvasPanel3D* grid_3d)
{
	if(v.empty()) return;
	int x_res = 50;
	int y_res = 50;
	float intervalx = 1.f/x_res;
	float intervaly = 1.f/y_res;
	float* a = new float[x_res*y_res];
	std::memset(a,0,sizeof(int)*x_res*y_res);

	for(auto i:v)
	{
		for(int j=0;j<x_res;++j)
		{
			if(i.x>j*intervalx&&i.x<(j+1)*intervalx)
			{
				for(int k=0;k<y_res;++k)
				{
					if(i.y>k*intervaly&&i.y<(k+1)*intervaly)
					{
						a[j+k*x_res]=a[j+k*x_res]+1.f;
						goto label;
					}
				}
			}
		}
		label:;
	}
	
	//�ܳ���
	int rew = grid_3d->get_res_w();
	//�ܿ��
	int reh = grid_3d->get_res_h();

	for(int i=0;i<y_res;++i)
	{
		for(int j=0;j<x_res;++j)
		{
			if(abs(a[j+i*x_res])<0.01)
				continue;
			float val =  ((float)a[j+i*x_res])/v.size()*x_res*y_res;
			float yp = ((float)i)/y_res;
			float xp = ((float)j)/x_res;
			grid_3d->set_px( xp*rew,yp*reh,val,ofColor::green,0.2);


		}
	}

}

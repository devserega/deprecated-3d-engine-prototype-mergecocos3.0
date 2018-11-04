// Inputs
attribute vec2 a_position;
attribute vec2 a_texCoord;

// Varying
varying vec2 v_texCoord;
varying float v_power;


#define MAX_CLICKS	8

// vec4.xy	����λ��
// vec4.z	Ӱ��뾶
// vec4.w	���뾶
uniform vec4 u_clicks[MAX_CLICKS];

void main()
{
    gl_Position = vec4(a_position, 0.0, 1.0);
    
    vec2 offset = vec2(0.0, 0.0);
    for (int i = 0; i < MAX_CLICKS; i++)
    {
	    vec4 click = u_clicks[i];
    //click.z = 0.01;
    	if ( click.z > 0.0 )
    	{
    		vec2 dir = a_texCoord-click.xy;
    		float dis = length(dir);
    			
    			
    		if ( dis < click.z )
    		{
    			// ��������
    			//float offDis = dis/click.z;
    			//offset -= (1.0-offDis)*dis*normalize(dir);
    			
    			
    			
    			float offDis = dis/click.z;
    			offDis = (1.0-offDis);
    			
    			float halfWavelength = 0.5*click.w;		// ����
    			halfWavelength *= max((1.0-click.z/click.w), 0.25)*2.0;
    			float crest = click.z-halfWavelength;	// ����
    			
				float disToCrest = min(abs(dis-crest), halfWavelength);	// �ನ�����
    			disToCrest = 1.0-(disToCrest/halfWavelength);	// �ನ��ֵΪ1.��ԵֵΪ0
    			offDis *= disToCrest;	// ����˥��
    			
    			offDis *= (1.0-click.z/click.w)*2.0;	//��뾶����˥��
    			
    			offset -= offDis*dis*normalize(dir);
    		}
    	}
    }
    
    v_texCoord = a_texCoord+offset;
}
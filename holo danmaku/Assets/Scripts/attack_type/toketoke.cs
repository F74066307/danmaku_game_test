using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class toketoke : MonoBehaviour {
	public GameObject bulletype;
	public GameObject bulletype2;
	public GameObject bulletype3;
	public int num=6;
	public int start_angle=0;
	public int sep_num=2;
	// Use this for initialization
	void Start () {
		//InvokeRepeating("shoot",2,3);
	}
	
	// Update is called once per frame
	void Update () {
		
	}

	public void shoot(){
		for(int i=0;i<num;i++){
			float pos_sep=0.3f;
			for(int j=0;j<sep_num;j++){
				if(j==0){
					GameObject b1 = Instantiate(bulletype);
                    b1.transform.position = transform.position;
                    b1.GetComponent<bulletmove>().theta = start_angle + 360/num*i;
                    b1.GetComponent<bulletmove>().start = 0f;
                    b1.GetComponent<bulletmove>().v = 0.01f;
                    b1.GetComponent<bulletmove>().type = 1;
                    b1.GetComponent<bulletmove>().r = 1.2f;
				}
				else{
					Vector3 step=new Vector3(pos_sep*Mathf.Sin((start_angle+i*360/num)*Mathf.Deg2Rad),-pos_sep*Mathf.Cos((start_angle+i*360/num)*Mathf.Deg2Rad),0);
					GameObject b1 = Instantiate(bulletype2);
                    b1.transform.position = transform.position+step*j;
                    b1.GetComponent<bulletmove>().theta = start_angle+360/num*i;
                    b1.GetComponent<bulletmove>().start = 0f;
                    b1.GetComponent<bulletmove>().v = 0.01f;
                    b1.GetComponent<bulletmove>().type = 1;
                    b1.GetComponent<bulletmove>().r = 1.2f-0.1f*j;

					GameObject b2 = Instantiate(bulletype3);
                    b2.transform.position = transform.position-step*j;
                    b2.GetComponent<bulletmove>().theta = start_angle+360/num*i;
                    b2.GetComponent<bulletmove>().start = 0f;
                    b2.GetComponent<bulletmove>().v = 0.01f;
                    b2.GetComponent<bulletmove>().type = 1;
                    b2.GetComponent<bulletmove>().r = 1.2f-0.1f*j;
				}
			}
		}
	}
}

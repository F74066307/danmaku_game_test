using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class wind_newtype : MonoBehaviour {
	public GameObject bulletype;
    public float frequency=0.04f;
    public float endtime;
    public float starttime;
    public int num=5;
    public int direct=1;
	public float a=0.5f;
	public float v=5f;
    float change;
    int count;
	float time=0;
	// Use this for initialization
	void Start () {
		change = 0;
		Invoke("to_start",1);
		Invoke("to_change_direct",2);
		Invoke("to_end",3);
	}
	
	// Update is called once per frame
	void Update () {
		
	}

	void create_wind(){
		for (int i=0; i<num;i++)
        {
            GameObject b1 = Instantiate(bulletype);
            b1.transform.position = transform.position+(new Vector3(0.15f*Mathf.Sin((360/num*i+change)*Mathf.PI/180), 0.15f*Mathf.Cos((360/num*i + change) * Mathf.PI / 180)));
            b1.GetComponent<bulletmove>().theta = (i*360/num+change);
            b1.GetComponent<bulletmove>().start = 0f;
            b1.GetComponent<bulletmove>().v = 0.02f;
            b1.GetComponent<bulletmove>().type = 1;
            b1.GetComponent<bulletmove>().r = 1f+count*0.2f;
        }
        change+=2*direct;
		//v=v*2;
        count++;
	}

	public void to_start(){InvokeRepeating("create_wind", starttime, frequency);}
    public void to_end() { CancelInvoke("create_wind"); change=0;count=0;}
	public void to_change_direct()
	{
		direct*=-1; 
		//change=0;
		count=0;
	}
}

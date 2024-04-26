using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class wind : MonoBehaviour {
    public GameObject bulletype;
    public GameObject bulletype2;
    public float frequency;
    public float endtime;
    public float starttime;
    public int num;
    public int direct;
    float change;
    int count;
    // Use this for initialization
    void Start () {

        //InvokeRepeating("create_wind", starttime, frequency);
        //Invoke("toend",endtime);
        change = 0;
    }

    public void create_wind()
    {
        
        for (int i=0; i<num;i++)
        {
            GameObject b1;
            if (i%2==0)
            {
                b1 = Instantiate(bulletype);
            }
            else
            {
                b1 = Instantiate(bulletype2);
            }
            b1.transform.position = transform.position+(new Vector3(0.1f*Mathf.Sin((360/num*i+change)*Mathf.PI/180), 0.1f*Mathf.Cos((360/num*i + change) * Mathf.PI / 180)));
            b1.GetComponent<bulletmove>().theta = (i*360/num+change);
            b1.GetComponent<bulletmove>().start = 0f;
            b1.GetComponent<bulletmove>().v = 0.01f;
            b1.GetComponent<bulletmove>().type = 1;
            b1.GetComponent<bulletmove>().r = 3;
        }
        change+=3*direct;
        count++;
    }
    public void to_start(){InvokeRepeating("create_wind", starttime, frequency);}
    public void to_end() { CancelInvoke("create_wind"); }

	
	// Update is called once per frame
	void Update () {
		
	}
}

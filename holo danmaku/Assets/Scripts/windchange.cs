using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class windchange : MonoBehaviour {
    public GameObject bulletype;
    public int num;
    public int num2;
    public float frequency;
    public float starttime;
    public float endtime;
    public float a;
    float change = 0;
	// Use this for initialization
	void Start () {
        InvokeRepeating("create_windchange", starttime, frequency);
        Invoke("toend", endtime);
        change = 0;
    }
	
    void create_windchange()
    {
        for (int i=0; i<num;i++)
        {
            for (int j=0; j<num2;j++)
            {
                GameObject b1 = Instantiate(bulletype);
                b1.transform.position = transform.position + (new Vector3(0.1f * Mathf.Sin((360 / num * i) * Mathf.PI / 180), 0.1f * Mathf.Cos((360 / num * i ) * Mathf.PI / 180)));
                b1.GetComponent<bulletmove>().theta = (i * 360 / num + change+j*3);
                b1.GetComponent<bulletmove>().start = 0f;
                b1.GetComponent<bulletmove>().v = 0.02f;
                b1.GetComponent<bulletmove>().type = 1;
                b1.GetComponent<bulletmove>().r = 3;
                b1.GetComponent<bulletmove>().a = a*j;

            }
        }
        a = -a;
    }

    void toend() { CancelInvoke("create_windchange"); }

    // Update is called once per frame
    void Update () {
		
	}
}

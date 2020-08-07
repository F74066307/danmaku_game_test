using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class star : MonoBehaviour {
    public GameObject bulletype;
    public int num;
    public int num2;
    public float frequency;
    public float starttime;
    public float endtime;
    public float a;
    public float r;
    
    // Use this for initialization
    void Start () {
        InvokeRepeating("create_star", starttime, frequency);
        Invoke("toend", endtime);
        
    }

    void create_star()
    {
        for (int i = 0; i < num; i++)
        {
            for (int j = 0; j<num2; j++)
            {
                GameObject b1 = Instantiate(bulletype);
                b1.transform.position = transform.position + (new Vector3(0.1f * Mathf.Sin((360 / num * i+j*10) * Mathf.PI / 180), 0.1f * Mathf.Cos((360 / num * i+j*10) * Mathf.PI / 180)));
                b1.GetComponent<bulletmove>().theta = (i * 360 / num  + j);
                b1.GetComponent<bulletmove>().start = 0f;
                b1.GetComponent<bulletmove>().v = 0.02f;
                b1.GetComponent<bulletmove>().type = 1;
                b1.GetComponent<bulletmove>().r = r;
                b1.GetComponent<bulletmove>().a = a * (num2-j);

                GameObject b2 = Instantiate(bulletype);
                b2.transform.position = transform.position + (new Vector3(0.1f * Mathf.Sin((360 / num * i-j*10) * Mathf.PI / 180), 0.1f * Mathf.Cos((360 / num * i-j*10) * Mathf.PI / 180)));
                b2.GetComponent<bulletmove>().theta = (i * 360 / num - j);
                b2.GetComponent<bulletmove>().start = 0f;
                b2.GetComponent<bulletmove>().v = 0.02f;
                b2.GetComponent<bulletmove>().type = 1;
                b2.GetComponent<bulletmove>().r = r;
                b2.GetComponent<bulletmove>().a = a * (num2-j);

            }
        }
    }

    void toend() { CancelInvoke("create_windchange"); }

    // Update is called once per frame
    void Update () {
		
	}
}

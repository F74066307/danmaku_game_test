using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ring : MonoBehaviour {
    public GameObject bulletype;
    public float start;
    public float frequency;
    public int ring_num;
    public int sep;
    public float a;
	// Use this for initialization
	void Start () {
        //InvokeRepeating("ring_attack",start,frequency);
	}

    public void ring_attack()
    {
        for (int i=0;i<ring_num;i++)
        {
            for (int j=0; j<sep;j++)
            {
                GameObject b1 = Instantiate(bulletype);
                b1.transform.position = transform.position;
                b1.GetComponent<bulletmove>().theta = (j*360/sep);
                b1.GetComponent<bulletmove>().start = 0f;
                b1.GetComponent<bulletmove>().v = 0.01f;
                b1.GetComponent<bulletmove>().type = 1;
                b1.GetComponent<bulletmove>().r = 1;
                b1.GetComponent<bulletmove>().a = a*i;
            }
        }
    }
	
	// Update is called once per frame
	void Update () {
		
	}
}

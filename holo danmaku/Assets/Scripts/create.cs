using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class create : MonoBehaviour {
    public GameObject bulletype;
    float change;
    int count = 0;
    
	// Use this for initialization
	void Start () {
        change = 120;
        InvokeRepeating("create_bullet",0.3f,0.03f);
	}

    void create_bullet()
    {
        for(int i=0;i<4;i++){
            GameObject b1 = Instantiate(bulletype);
        b1.transform.position = transform.position;
        b1.GetComponent<bulletmove>().theta = (change);
        b1.GetComponent<bulletmove>().start = 6f-0.03f*count;
        b1.GetComponent<bulletmove>().start2 = 8f-0.03f*count;
        b1.GetComponent<bulletmove>().v = 0.03f;
        b1.GetComponent<bulletmove>().type = 2;
        b1.GetComponent<bulletmove>().r = 3;
        b1.GetComponent<bulletmove>().t=108*i;
        }
        //change += 180 * Time.deltaTime;
        change -=8 ;
        count++;
    }
	
	// Update is called once per frame
	void Update () {
       

    }
}

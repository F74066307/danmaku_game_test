using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ring_type_move : MonoBehaviour {
    public float change_time;
    public int num;
    float count;
    float v;
    float r=0;
    int  angle=1;
    float f;
    float theta;
    GameObject moto;
	// Use this for initialization
	void Start () {
        moto = GameObject.Find("senchou");
        f = 0.3f;
        v = gameObject.GetComponent<bulletmove>().r;
        count = 36;//0 / gameObject.GetComponent<ring>().sep;
        InvokeRepeating("move_ring", change_time, f);
        theta = gameObject.GetComponent<bulletmove>().theta;
    }

    void move_ring()
    {
        r = 1;//(transform.position - moto.transform.position).magnitude;
        transform.position = moto.transform.position + new Vector3(r * Mathf.Sin(theta), r * Mathf.Cos(theta), 0) * Time.deltaTime;
        theta = theta + angle * Mathf.PI / 180;
        gameObject.GetComponent<bulletmove>().r = 0;
        gameObject.GetComponent<bulletmove>().a = 0;
        count-=f;
        //gameObject.GetComponent<bulletmove>().angle = 1;
        if (count<=0)
        {
            CancelInvoke("move_ring");
            gameObject.GetComponent<bulletmove>().r= v;
        }
        
    }

    void move_straight()
    {

    }
	
	// Update is called once per frame
	void Update () {
        
    }
}

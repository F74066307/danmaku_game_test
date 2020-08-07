using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class bulletmove : MonoBehaviour {

    // Use this for initialization
    public float r = 0;
    public float t;
    public float theta;
    public int angle = 0;
    public float start,start2, v;
    public float a = 0;
    public int type=0;
    //GameObject launch = GameObject.Find("matsuri");
    public void fly()
    {
        if(type==3){
            CancelInvoke("change_pos");
        }
        transform.position +=new Vector3(r*Mathf.Cos(theta), r * Mathf.Sin(theta),0)*Time.deltaTime;
        //theta += Time.deltaTime;
        theta = theta + angle * Mathf.PI / 180;
        r = r + a;
    }

    public void change_pos(){
        
        transform.position +=new Vector3(r*Mathf.Cos(t), r * Mathf.Sin(t),0)*Time.deltaTime;
        //theta += Time.deltaTime;
    }

    

	void Start () {
        //InvokeRepeating("fly",start,v);
        theta = theta * Mathf.PI / 180;
	}
	
	// Update is called once per frame
	void Update () {
        // fly();
        switch (type)
        {
            case 0:
                fly();
                break;
            case 1:
                InvokeRepeating("fly", start, v);
                type = -1;
                break;
            case 2:
                InvokeRepeating("change_pos", start, v);
                InvokeRepeating("fly", start2, v);
                type=3;
                break;
            default:
                break;
        }
        if ((transform.position.y>5.5 ||transform.position.y<-5.5)||(transform.position.x>8.8)||transform.position.x<-8.8)
        {
            Destroy(this.transform.gameObject);
           
        }
	}
}

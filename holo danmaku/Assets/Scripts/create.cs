using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class create : MonoBehaviour {
    public GameObject bulletype;
    public GameObject bulletype2;
    float change;
    int count = 0;
    
	// Use this for initialization
	void Start () {
        change = 0;
        InvokeRepeating("create_bullet",0.3f,0.03f);
	}
    public void start_to_attack(){
        
    }
    void create_bullet()
    {
        for(int i=0;i<4;i++){
            GameObject b1;
            if(i%2==0){
                 b1= Instantiate(bulletype);
            }  
            else
            {
                b1= Instantiate(bulletype2);
            }
            b1.transform.position = transform.position;
            b1.GetComponent<bulletmove>().theta = (change);
            b1.GetComponent<bulletmove>().start = 5f-0.03f*count;
            b1.GetComponent<bulletmove>().start2 = 6.3f-0.03f*count;
            b1.GetComponent<bulletmove>().v = 0.03f;
            b1.GetComponent<bulletmove>().type = 2;
            b1.GetComponent<bulletmove>().r = 3;
            b1.GetComponent<bulletmove>().t=108*i;
        }
        //change += 180 * Time.deltaTime;
        change -=15 ;
        count++;
    }
	
	// Update is called once per frame
	void Update () {
       

    }
}

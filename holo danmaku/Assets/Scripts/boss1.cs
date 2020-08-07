using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class boss1 : MonoBehaviour {
    public GameObject bulletype;
    float change;
    int count=0;
    float speed=0.1f;
    float time_to_change_direction=5;
    float is_time_to_change=0;
	// Use this for initialization
	void Start () {
        //InvokeRepeating("attack", 0f, 0.03f);
        change=Random.Range(-5,6);
        change=Mathf.Sign(change);
    }

    void attack()
    {
        
        GameObject b1 = Instantiate(bulletype);
        b1.transform.position = transform.position - new Vector3(Mathf.Sin(change * Mathf.PI / 180)*speed, Mathf.Cos(change * Mathf.PI / 180)*speed, 0);
        b1.GetComponent<bulletmove>().theta = (change+90) * Mathf.PI / 180;
        b1.GetComponent<bulletmove>().start = 0f;
        b1.GetComponent<bulletmove>().v = 0.1f;
        change += 180 * Time.deltaTime;
    }
	
	// Update is called once per frame
	void Update () {
        //InvokeRepeating("attack",0f,10f);
        count++;
        transform.Translate(2*change* Time.deltaTime, 0, 0);
        is_time_to_change+=Time.deltaTime;
        if(is_time_to_change>time_to_change_direction){
                change=Random.Range(-5,6);
                change=Mathf.Sign(change);
                is_time_to_change=0;
        }
        
    }
}

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class specialmove : MonoBehaviour {
    // Use this for initialization
    int now = 0;
    float starttime=0.3f;
    public int line=50;
    void Start () {
      gameObject.GetComponent<bulletmove>().r=0;
	}
	
	// Update is called once per frame
	void Update () {
        starttime-=Time.deltaTime;
        if(starttime<=0){
        gameObject.GetComponent<bulletmove>().r=5;
        
        if (now <= line)
        {
            gameObject.GetComponent<bulletmove>().theta= 72 * Mathf.PI / 180;

        }
        else if (now > line && now <= line*2)
        {

            gameObject.GetComponent<bulletmove>().theta = -144 * Mathf.PI / 180;
        }
        else if (now > line*2 && now <= line*3)
        {

            gameObject.GetComponent<bulletmove>().theta = 0 * Mathf.PI / 180;
        }
        else if (now > line*3 && now <= line*4)
        {

            gameObject.GetComponent<bulletmove>().theta = -216 * Mathf.PI / 180;
        }
        else if (now > line*4 && now <= line*5)
        {
            gameObject.GetComponent<bulletmove>().theta = -72 * Mathf.PI / 180;
        }
        else
        {
            gameObject.GetComponent<bulletmove>().r = 0;
            gameObject.GetComponent<create>().CancelInvoke("create_bullet");
            gameObject.GetComponent<create_star>().CancelInvoke("create_bullet");
            //now = 0;
        }
        now++;
        }
    }
}

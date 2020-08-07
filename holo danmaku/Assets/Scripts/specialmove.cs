using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class specialmove : MonoBehaviour {
    // Use this for initialization
    int now = 0;
    float starttime=0.3f;
    void Start () {
      gameObject.GetComponent<bulletmove>().r=0;
	}
	
	// Update is called once per frame
	void Update () {
        starttime-=Time.deltaTime;
        if(starttime<=0){
        gameObject.GetComponent<bulletmove>().r=5;
        
        if (now <= 50)
        {
            gameObject.GetComponent<bulletmove>().theta= 72 * Mathf.PI / 180;

        }
        else if (now > 50 && now <= 100)
        {

            gameObject.GetComponent<bulletmove>().theta = -144 * Mathf.PI / 180;
        }
        else if (now > 100 && now <= 150)
        {

            gameObject.GetComponent<bulletmove>().theta = 0 * Mathf.PI / 180;
        }
        else if (now > 150 && now <= 200)
        {

            gameObject.GetComponent<bulletmove>().theta = -216 * Mathf.PI / 180;
        }
        else if (now > 200 && now <= 250)
        {
            gameObject.GetComponent<bulletmove>().theta = -72 * Mathf.PI / 180;
        }
        else
        {
            gameObject.GetComponent<bulletmove>().r = 0;
            gameObject.GetComponent<create>().CancelInvoke("create_bullet");
            //now = 0;
        }
        now++;
        }
    }
}

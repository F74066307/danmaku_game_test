using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class createflower : MonoBehaviour {
    float angle = 150;
    public GameObject bulletype;
    int count = 0;
    public float r;
	// Use this for initialization
	void Start () {
        
        InvokeRepeating("create_flower", 0f, 0.02f);
        InvokeRepeating("stop", 10f, 5f);

    }
    void stop() { CancelInvoke("create_flower"); }

    void create_flower()
    {
        for (int i=0; i<5;i++)
        {
            GameObject b1 = Instantiate(bulletype);
            b1.transform.position = transform.position+new Vector3(r * Mathf.Sin(72*i * Mathf.PI / 180), r * Mathf.Cos((72*i) * Mathf.PI / 180), 0)+ new Vector3(3 * Mathf.Sin((angle+75*i) * Mathf.PI / 180), 3 * Mathf.Cos((angle+75*i) * Mathf.PI / 180), 0) ;
            b1.GetComponent<bulletmove>().theta = (( angle+300* i) );
            b1.GetComponent<bulletmove>().start = 5f;// + 0.02f * count;
            b1.GetComponent<bulletmove>().v = 0.03f;
            b1.GetComponent<bulletmove>().type = 1;
            b1.GetComponent<bulletmove>().r = 3;
            //change += 180 * Time.deltaTime;
            angle += 1;
            count++;
            if (count==245)
            {
                stop();
            }
        }
    }
	
	// Update is called once per frame
	void Update () {
		
	}
}

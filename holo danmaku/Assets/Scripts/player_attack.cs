using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class player_attack : MonoBehaviour {

    public GameObject bullettype;

	// Use this for initialization
	void Start () {
        InvokeRepeating("attack", 0, 0.1f);
    }
	
    void attack()
    {
        GameObject b1 = Instantiate(bullettype);
        b1.transform.position = transform.position;
        b1.GetComponent<bulletmove>().theta = (0);
        b1.GetComponent<bulletmove>().r = 10;
    }

	// Update is called once per frame
	void Update () {
        
    }
}

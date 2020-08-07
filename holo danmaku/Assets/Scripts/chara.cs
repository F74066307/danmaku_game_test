using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class chara : MonoBehaviour {

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
        if (Input.GetKey("down")|| Input.GetKey(KeyCode.S))
        {
            transform.Translate(0, -2f * Time.deltaTime, 0);
        }
        if (Input.GetKey("left") || Input.GetKey(KeyCode.A))
        {
            transform.Translate(-2f * Time.deltaTime, 0, 0);
            
        }
        if (Input.GetKey("up") || Input.GetKey(KeyCode.W))
        {
            transform.Translate(0, 2f * Time.deltaTime, 0);
        }
        if (Input.GetKey("right") || Input.GetKey(KeyCode.D))
        {
            transform.Translate(2f * Time.deltaTime, 0, 0);
            
        }

    }
}

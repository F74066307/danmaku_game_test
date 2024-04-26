using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class shoot_player : MonoBehaviour {
	public GameObject bulletype;
	Vector3 player_position;
	// Use this for initialization
	void Start () {
		InvokeRepeating("shoot",3,1);
		
		//shoot();
	}
	
	// Update is called once per frame
	void Update () {

	}

	void shoot(){
		//GameObject player=GameObject.Find("player(Clone)");
		GameObject player=GameObject.FindGameObjectWithTag("Player");
		player_position=player.transform.position;
		for(int i=0;i<4;i++){
			GameObject b1=Instantiate(bulletype);
			b1.transform.position=transform.position;//+new Vector3(1f*Mathf.Sin(60*Mathf.PI*(i-1)/180),1f*Mathf.Cos(60*Mathf.PI*(i-1)/180),0);
			b1.GetComponent<bulletmove>().calc_angle(player_position,transform.position);
			b1.GetComponent<bulletmove>().start = 0f;
            b1.GetComponent<bulletmove>().v = 0.01f;
            b1.GetComponent<bulletmove>().type = 1;
            b1.GetComponent<bulletmove>().r = 1;
			b1.GetComponent<bulletmove>().a=0.1f*(4-i);
			b1.GetComponent<bulletmove>().r_limit=1.5f;
		}
	}
}

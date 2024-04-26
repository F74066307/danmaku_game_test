using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class hit_check : MonoBehaviour {
	public GameObject dead_effect;
	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}

	private void OnTriggerEnter2D(Collider2D collision)
    {
		if (collision.gameObject.tag == "Enemy_shot")
        {
			GameObject pde = Instantiate(dead_effect,transform.position+(new Vector3(0,0.5f,0)),Quaternion.identity);
			Destroy(pde, 1.5f);
			GameObject score_m=GameObject.FindGameObjectWithTag("PlayerManager");
			score_m.GetComponent<PlayerManager>().Destroy_Player();

        }
    }
}

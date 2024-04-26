using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class muteki_time : MonoBehaviour {
	GameObject heart;
	SpriteRenderer s_renderer;
	float check_time;
	int cnt=0;
	// Use this for initialization
	void Start () {
		heart=GameObject.FindGameObjectWithTag("PlayerHeart");
		s_renderer=GetComponent<SpriteRenderer>();
		check_time=Time.time;
	}
	
	// Update is called once per frame
	void Update () {
		if(Time.time-check_time<=2.5f){
			CalcApha();
		}
		else{
			GameObject score_m=GameObject.FindGameObjectWithTag("PlayerManager");
			int fire_on=GetComponent<new_chara_move>().fire_on;
			score_m.GetComponent<PlayerManager>().Respawn_Player(transform.position,fire_on);
			Destroy(gameObject);
		}
	}

	void CalcApha(){
		++cnt;
        float alpha = (Mathf.Sin(cnt * 120))/2+0.5f;
        s_renderer.color = new Color(1, 1, 1, alpha);
	}
}

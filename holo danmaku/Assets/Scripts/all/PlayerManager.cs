using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerManager : MonoBehaviour {
	public GameObject player_model;
	public GameObject muteki_player;
	public GameObject respawn_effect;
	private Vector3 respawn_position=new Vector3(-1.0f,-4.4f,0f);
	public int now_life{get;set;}
	public GameObject life_count;
	private List<GameObject> player_life=new List<GameObject>();
	public GameObject life_bar;
	public GameObject GameOverUI;
    public AudioClip killed;
	//public int now_life=5;
	// Use this for initialization
	void Start () {
		//respawn_position=new Vector3(-1.0f,-4.4f,0f);
		//Respawn_Player();
		Respawn_Muteki_time();
		now_life=5;
		for(int i=0;i<now_life;i++){
			GameObject a=Instantiate(life_count,life_count.transform.position+new Vector3(0.5f*i,0f,0f),Quaternion.identity);
			//a.transform.parent=GameObject.FindGameObjectWithTag("PlayerLifeBar").transform;
			//a.transform.SetParent(life_bar.transform);
			//a.transform.localScale=new Vector3(6,6,1);
			//a.transform.position=new Vector3(2f,2f,0f);
			player_life.Add(a);
		}
	}
	
	// Update is called once per frame
	void Update () {
		
	}

	public void Destroy_Player(){
		GameObject dead_player=GameObject.FindGameObjectWithTag("Player");
		Destroy(dead_player);
		if(now_life>0){
			//Respawn_Muteki_time();
			AudioSource.PlayClipAtPoint(killed,GameObject.FindGameObjectWithTag("MainCamera").transform.position,0.12f);
			now_life--;
			Invoke("Respawn_Muteki_time",1f);
			Destroy(player_life[now_life]);
		    player_life.RemoveAt(now_life);
			//Respawn_Player();
		}
		else
		{
			Invoke("GameOver", 2f);
		}
	}

	void Respawn_Muteki_time(){
		GameObject muteki_p=Instantiate(muteki_player,new Vector3(-2.2f,-4.4f,0f),Quaternion.identity);
	}

	public void Respawn_Player(Vector3 pos,int fire_on){
		GameObject now_player = Instantiate(player_model,pos,Quaternion.identity);
		now_player.transform.position=pos;
		now_player.GetComponent<new_chara_move>().fire_on=fire_on;
		GameObject pre = Instantiate(respawn_effect,now_player.transform.position,Quaternion.identity);
		Destroy(pre, 2.0f);
	}

	public void GameOver(){
		GameOverUI.SetActive(true);
	}

}

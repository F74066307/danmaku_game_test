using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class pol_dan_attack : MonoBehaviour {

	float Speed = 0.01f;
	private int maxHp=100;
	private Slider hp_bar;
	bool first=true;
	int Life;
    CGameManager GameManager;
	Animator anim;
	AudioSource audioSource;
	bool ready_to_attack=false;

	public int attack_type;
	public ring launcher;
	public wind launcher2;
	public toketoke launcher3;
	public GameObject launcher4;
	public GameObject launcher5;
	public int attack_frequency;
	public float left_limit;
	public float right_limit;
	public float y_limit{get;set;}
	public GameObject dead_effect;
	public GameObject slider;
	public int enemy_score;
	public AudioClip killed;
	
	// Use this for initialization
	void Start () {
		anim = GetComponent<Animator>();
		audioSource = GetComponent<AudioSource>();
		InvokeRepeating("attack",0,attack_frequency);
		if(attack_type==4){
			maxHp=700;
		}
		Life=maxHp;
		hp_bar=slider.GetComponent<Slider>();
		hp_bar.value=1.0f;
	}
	
	// Update is called once per frame
	void Update () {
		if(transform.position.y>3.0f){
			transform.position+=new Vector3(0,-0.1f,0);
		}
		else{
			ready_to_attack=true;
			if(transform.position.x>=right_limit||transform.position.x<=left_limit){
				Speed=-Speed;
			}
			if(first){
				anim.SetBool("is_attack",true);
				first=false;
			}
			if(!anim.GetBool("is_attack")){
				transform.position+=new Vector3(Speed,0,0);
			}

		}
		
	}

	void attack(){
		if(ready_to_attack){
			anim.SetBool("is_attack",true);
		}
	}

	void to_attack(){
		if(anim.GetBool("is_attack")){
			if(attack_type==1){
				launcher.ring_attack();
			}
			else if(attack_type==2){
				launcher2.to_start();
			}
			else if(attack_type==3){
				launcher3.shoot();
			}
			else if(attack_type==4) 
			{
				GameObject b1;
				int a=Random.Range(0,200);
				if(a%2==0){
					b1= Instantiate(launcher4);
				}
				else{
					b1= Instantiate(launcher5);
				}
				
                b1.transform.position = transform.position-new Vector3(0f,3f,0f);
			}
		}
	}

	void attack_end(){
		anim.SetBool("is_attack",false);
		if(attack_type==2){
			launcher2.to_end();
		}
	}
	private void OnTriggerEnter2D(Collider2D collision)
    {
		if (collision.gameObject.tag == "Shot"&&Life>0)
        {
			Life -= collision.gameObject.GetComponent<CShot>().ShotPower;
			hp_bar.value=((float)Life/(float)maxHp);
			if(Life<=0){
				AudioSource.PlayClipAtPoint(killed,GameObject.FindGameObjectWithTag("MainCamera").transform.position,0.12f);
				GameObject score_m=GameObject.FindGameObjectWithTag("ScoreManager");
				score_m.GetComponent<ScoreUp>().AddScore(enemy_score);
				GameObject enemy_m=GameObject.FindGameObjectWithTag("EnemyManager");
				enemy_m.GetComponent<EnemyManager>().now_enemy_num-=1;
				enemy_m.GetComponent<EnemyManager>().enemy_defeat+=1;
				//enemy_m.GetComponent<EnemyManager>().manage_enemy();
				Destroy(gameObject);
				GameObject ede = Instantiate(dead_effect,transform.position+(new Vector3(0,0.5f,0)),Quaternion.identity);
				Destroy(ede, 1.5f);
				
			}
        }
    }

	
}

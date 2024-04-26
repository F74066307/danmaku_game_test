using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class EnemyManager : MonoBehaviour {
	private GameObject[] enemy_type;
	public int now_enemy_num{get;set;}
	public int full_enemy_num=2;
	int now_full=2;
	public int enemy_defeat=0;
	private float time=0f;
	// Use this for initialization
	void Start () {
		enemy_type=Resources.LoadAll<GameObject>("Enemy_prefab");
		now_enemy_num=0;
		
	}
	
	// Update is called once per frame
	void Update () {
		if(now_enemy_num<full_enemy_num){
			now_enemy_num++;
			Invoke("summon_enemy",1.0f);
		}
	}
	public void manage_enemy(){
		if(now_enemy_num<full_enemy_num){
			Invoke("summon_enemy",1.0f);
		}
	}
	void summon_enemy(){
		if(now_enemy_num>full_enemy_num){
			now_enemy_num--;
		}
		else{
			//now_enemy_num++;
			int to_summon=0;
			if(enemy_defeat>0&&enemy_defeat%10==0){
				
				to_summon=0;
				full_enemy_num=1;
			}
			else
			{
				if(full_enemy_num==1){
					now_full++;
					full_enemy_num=now_full;
				}
				to_summon=Random.Range(1,enemy_type.Length);
			}
		    float summon_x=Random.Range(-6.4f,1.5f);
			float summon_y=Random.Range(2.5f,3.5f);
		    GameObject summon=Instantiate(enemy_type[to_summon],new Vector3(summon_x,6.5f,0f),Quaternion.identity);
		    summon.GetComponent<pol_dan_attack>().left_limit=summon.transform.position.x-1.0f;
		    summon.GetComponent<pol_dan_attack>().right_limit=summon.transform.position.x+1.0f;
			summon.GetComponent<pol_dan_attack>().y_limit=summon_y;
		}
	}
}

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ScoreUp : MonoBehaviour {
	
	public GameObject HiScore_obj;
	public GameObject Score_obj;
	private Text HiScoreText;
	private Text ScoreText;
	private int nowScore;
	private int Score;
	private int highScore=0;
	// Use this for initialization
	void Start () {
		HiScoreText=HiScore_obj.GetComponent<Text>();
		ScoreText=Score_obj.GetComponent<Text>();
		nowScore=Score=0;
		HiScoreText.text="HiScore:"+highScore;
		ScoreText.text="Score:"+nowScore;
	}
	
	// Update is called once per frame
	void Update () {
		ScoreText.text="Score: "+Score;
		if(nowScore!=Score){
			//nowScore++;
			//ScoreText.text="Score: "+nowScore;
		}
	}
	public void GameOver_Score(){
		highScore=Score;
	}
	public void AddScore(int to_add){
		Score+=to_add;
	}
}

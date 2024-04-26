using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class new_chara_move : MonoBehaviour {

	// Use this for initialization
    public GameObject[] ShotObjs;

    //int now_life=5;
	void Start () {
		Sqrt2 = 1.0f / Mathf.Sqrt(2.0f);
        InputArray["Fire1"] = 0;
        InputArray["Fire2"] = 0;
        InputArray["Fire3"] = 0;
        //fire_on=0;
	}
	float VX = 0;
    float VY = 0;
    float Sqrt2;
    //int fire_on=0;
    public int fire_on{get; set;}
    float attack_time_count=0;
	// Update is called once per frame
    Dictionary<string, int> InputArray = new Dictionary<string, int>();

    void CalcInput()
    {
        string[] str = { "Fire1", "Fire2", "Fire3" };
        for(int i = 0; i < str.Length; ++i)
        {
            if (Input.GetButton(str[i]))
            {
                ++InputArray[str[i]];
            }
            else
            {
                InputArray[str[i]] = 0;
            }
        }
    }
	void Update () {
        CalcInput();
        if(0 < InputArray["Fire1"] && InputArray["Fire1"] % 6 == 0){
            fire_on=1;
        }
        if(fire_on>0){
            attack_time_count+=Time.deltaTime;
        }
        VX = VY = 0 < InputArray["Fire3"] ? 2.5f * Time.deltaTime : 7.0f * Time.deltaTime;
        float x = Input.GetAxisRaw("Horizontal");
        float y = Input.GetAxisRaw("Vertical");

        if (x < 0) VX = -VX; else if(x == 0) VX = 0;
        if (y < 0) VY = -VY; else if(y == 0) VY = 0;
        
        if (VX != 0 && VY != 0)
        {
            VX = VX * Sqrt2;
            VY = VY * Sqrt2;
        }
        transform.position = CUtility.ClampPosition(new Vector3(transform.position.x+VX, transform.position.y+VY, 0));
	    if (fire_on>0&&attack_time_count>0.06)
        {
            CSoundPlayer.PlaySound("cshot", true);
            if (0 < InputArray["Fire3"])
            {
                LowerSpeedShot();
            }
            else 
            {
                HiSpeedShot();
            }
            attack_time_count=0;
        }
    }

    int[] CShot0Num = { 2, 4 };
    Vector3[] HiSpeedShotOffsetPos = 
    {
        new Vector3(-0.15f,0.8f),
        new Vector3(0.15f,0.8f),
        new Vector3(-0.45f,0.4f),
        new Vector3(0.45f,0.4f),
    };
    Vector3[] LowerSpeedShotOffsetPos =
    {
        new Vector3(-0.05f,0.8f),
        new Vector3(0.05f,0.8f),
        new Vector3(-0.25f,0.4f),
        new Vector3(0.25f,0.4f),
    };
    void HiSpeedShot()
    {
        //	Power < 200 ?0 : 1
        for (int i = 0; i < CShot0Num[1]; i++)
        {
            //SGP.Shot.Add(new CShot(X + CShot0Pos_X[i], Y + CShot0Pos_Y[i], 0.75f, 10));
            Instantiate(ShotObjs[0], transform.position+ HiSpeedShotOffsetPos[i], Quaternion.identity);
        }
    }
    void LowerSpeedShot()
    {
        for (int i = 0; i < CShot0Num[1]; i++)
        {
            //SGP.Shot.Add(new CShot(X + CShot0Pos_X[i], Y + CShot0Pos_Y[i], 0.75f, 10));
            Instantiate(ShotObjs[0], transform.position + LowerSpeedShotOffsetPos[i], Quaternion.identity);
        }
    }
    void attack_count_start(){
        
    }
    
    private void OnTriggerEnter2D(Collider2D collision)
    {
        if(collision.tag == "Bullet")
        {
            
            Destroy(gameObject);
            Destroy(collision.gameObject);
        }
    }
}

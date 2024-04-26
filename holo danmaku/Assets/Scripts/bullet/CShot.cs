using System.Collections;
using System.Collections.Generic;
using UnityEditor;
using UnityEngine;


public class CShot : MonoBehaviour {
	public float Speed = 15.0f;
    public int ShotPower = 1;
    public GameObject hit_effect;
	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		float angle = 90.0f;
        transform.position += CUtility.GetDirection360(angle) * Speed * Time.deltaTime;

        // 弾が進行方向を向くようにする
        var angles = transform.localEulerAngles;
        angles.z = angle - 90;
        transform.localEulerAngles = angles;

        // 2 秒後に削除する
        Destroy(gameObject, 2);
		
	}
    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.gameObject.tag == "Enemy")
        {
            GameObject ede = Instantiate(hit_effect, transform.position, Quaternion.identity);
            Destroy(ede, 1.5f);
            Destroy(gameObject);
        }
    }
}

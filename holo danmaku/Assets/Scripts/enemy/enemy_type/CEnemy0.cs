using System.Collections;
using System.Collections.Generic;
using UnityEditor;
using UnityEngine;
//移動パターン0 
//下がってきて停滞して上がっていく
public class CEnemy0 : CEnemy
{
    void Update()
    {
        if (Cnt == 0)
        {
            VY = -3.0f;
        }
        if (Cnt == 100)
        {
            VY = 0.0f;
            BulletDischarge = true;
        }
        if (Cnt == 100 + Wait)
        {
            VY = 3.0f;
            BulletDischarge = false;
        }

        transform.position += new Vector3(VX, VY, 0.0f) * Time.deltaTime;

        _Animator.SetFloat("H", VX);

        if (BulletController != null && BulletDischarge)
        {
            BulletController.Move(transform.position);
        }

        Cnt++;

        if (CUtility.IsOut(transform.position))
        {
            Destroy(gameObject);
        }
    }
    public static void New(TagEnemyStatus enemy_status)
    {
        GameObject enemy_obj = Instantiate(enemy_status.EnemyObj, new Vector3(enemy_status.X, enemy_status.Y, 0), Quaternion.identity);
        enemy_obj.AddComponent<CEnemy0>().EnemyStatus = enemy_status;
    }
}
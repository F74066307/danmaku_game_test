﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//行動パターン5
//斜め左下へ
public class CEnemy5: CEnemy
{
    void Update()
    {
        if (Cnt == 0)
        {
            VX = -3.0f;
            VY = -5.0f;
        }
        if (Cnt == 100)
        {
            BulletDischarge = true;
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
        enemy_obj.AddComponent<CEnemy5>().EnemyStatus = enemy_status;
    }
}

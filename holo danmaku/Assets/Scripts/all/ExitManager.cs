using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;

public class ExitManager : MonoBehaviour {

	// Use this for initialization
	void Start () {
		
	}
	public void ExitCurrentScene()
    {
        Application.Quit();
		//EditorApplication.isPlaying=false;
    }
	// Update is called once per frame
	void Update () {
		
	}
}

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class WebCamController : MonoBehaviour
{
    void Start()
    {
        // TODO the orientation is broken, need to fix this
	var rawImage = GetComponent<RawImage>();
	var webCamTexture = new WebCamTexture();
	rawImage.texture = webCamTexture;
	//material.mainTexture = webCamTexture;
	webCamTexture.Play();
    }
}

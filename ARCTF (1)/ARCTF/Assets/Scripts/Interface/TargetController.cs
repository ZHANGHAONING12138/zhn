using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class TargetController : MonoBehaviour
{
    void Update()
    {
        var text = GetComponent<Text>();
        var target = Target.GetTypeName();
        if (target == "")
        {
            text.text = "";
            return;
        }
        text.text = "Target:\n" + target;
    }
}

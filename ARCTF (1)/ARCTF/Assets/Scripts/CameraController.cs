using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraController : MonoBehaviour
{
    void Start()
    {
        Input.gyro.enabled = true;
        //Input.gyro.updateInterval = "0.01f";
    }

    void Update()
    {
        #if !UNITY_EDITOR // TODO debug
        transform.rotation = Input.gyro.attitude;
        transform.Rotate(0f, 0f, 180f, Space.Self);
        transform.Rotate(90f, 180f, 0f, Space.World);
        #else
        // in editor, move the camera using the cursor keys
        var mH = Input.GetAxis("Horizontal");
        var mV = Input.GetAxis("Vertical");
        transform.Rotate(-mV, mH, 0f, Space.Self);
        #endif

        Vector3 position;
        // do not continue if the user is not clicking/tapping
        if (!GetPointerPosition(out position)) return;
        var ray = GetComponent<Camera>().ScreenPointToRay(position);
        RaycastHit hit;
        // return the object which is clicked/tapped
        if (!Physics.Raycast(ray, out hit, 2.0f)) return;
        // set the current interaction target as this object
        Target.Set(hit.transform.gameObject);
    }

    // return the coordinates which the user is clicking/tapping
    private static bool GetPointerPosition(out Vector3 position)
    {
        if (Input.touchCount > 0)
        {
            var touch = Input.GetTouch(0);
            if (touch.phase == TouchPhase.Ended)
            {
                position = touch.position;
                return true;
            }
        }
        else if (Input.GetMouseButtonUp(0))
        {
            position = Input.mousePosition;
            return true;
        }
        position = Vector3.zero;
        return false;
    }
}

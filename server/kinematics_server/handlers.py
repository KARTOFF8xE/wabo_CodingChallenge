from .kinematics_cffi import get_version as kin_get_version, get_link_lengths, forward_kinematics
from .models import WaboLinksGetResponseItem, WaboKinematikResults
from typing import List
import numpy as np

def get_cartesian_position_impl(joint_position: List[float]) -> List[float]:
    if len(joint_position) != 2:
        raise ValueError("joint_position must have two elements")
    pos = forward_kinematics(joint_position[0], joint_position[1])
    return [pos["x"], pos["y"]]

def get_link_information_impl() -> List[WaboLinksGetResponseItem]:
    lengths = get_link_lengths()
    return [
        WaboLinksGetResponseItem(link_name="link0", length=lengths["length_0"]),
        WaboLinksGetResponseItem(link_name="link1", length=lengths["length_1"])
    ]

def get_version_impl() -> str:
    v = kin_get_version()
    return f'{v["major"]}.{v["minor"]}.{v["patch"]}'

def get_kinematicresults_impl(joint_position: List[float]) -> WaboKinematikResults:
    if len(joint_position) != 2:
        raise ValueError("joint_position must have two elements")
    theta0, theta1 = joint_position
    pos = forward_kinematics(theta0, theta1)

    links = get_link_lengths()
    L0 = links["length_0"]
    L1 = links["length_1"]
    x0, y0 = 0, 0
    x1 = np.cos(theta0) * L0
    y1 = np.sin(theta0) * L0
    x2 = x1 + np.cos(theta0 + theta1) * L1
    y2 = y1 + np.sin(theta0 + theta1) * L1
    return WaboKinematikResults(x0=x0, x1=x1, x2=x2, y0=y0, y1=y1, y2=y2, xpos=pos["x"], ypos=pos["y"])

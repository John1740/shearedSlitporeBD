#!/usr/bin/env python3.7
import numpy as np
from argparse import ArgumentParser
# from pathlib import Path
import math

def findSettingInString(string, substring):
    posKeyword = string.find(substring)
    posStart = string.find("_", posKeyword) + 1
    posEnd = string.find("_", posStart)
    setting = string[posStart:posEnd]
    return setting

class BoxGeometry:
    dimensions = np.zeros(3)
    boundaryMin = np.zeros(3)
    boundaryMax = np.zeros(3)
    origin = np.zeros(3)
    volume = 0

    def __init__(self, volume, d_wall):
        self.setDimensions(volume, d_wall)

    def setDimensions(self, volume, dWall):
        self.dimensions[2] = dWall
        self.volume = volume
        dx = math.sqrt(volume / dWall)
        self.dimensions[0] = dx
        self.dimensions[1] = dx
        self.boundaryMin = self.origin - self.dimensions / 2
        self.boundaryMax = self.origin + self.dimensions / 2

def main():
    parser = ArgumentParser(description="description")
    parser.add_argument("infile", help="input file of old configuration style")
    # parser.add_argument("--outfile", "-o", default="configuration.in", help="output file of new configuration style")
    args = parser.parse_args()

    # print(f"Reading {args.infile}")
    cfg_old = np.loadtxt(args.infile)
    xPos = cfg_old[:, 3]
    yPos = cfg_old[:, 4]
    zPos = cfg_old[:, 2]

    dWall = float(findSettingInString(args.infile, "Dwall"))
    rho = float(findSettingInString(args.infile, "rho"))
    N = int(findSettingInString(args.infile, "N"))
    volume = N / rho
    timestep = 0
    simBox = BoxGeometry(volume, dWall)

    fmt = " 2.5f"

    #print Header
    print("ITEM: TIMESTEP")
    print(f"{timestep}")
    print("ITEM: NUMBER OF ATOMS")
    print(f"{N}")
    print("ITEM: BOX BOUNDS xx yy zz")
    for i in range(3):
        print(f"{simBox.boundaryMin[i]:{fmt}}\t{simBox.boundaryMax[i]:{fmt}}")
    print("ITEM: ATOMS x y z")
    for i in range(len(xPos)):
        print(f"{xPos[i]:{fmt}}\t{yPos[i]:{fmt}}\t{zPos[i]:{fmt}}")

    return 0

if __name__ == '__main__':
    main()
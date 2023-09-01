def calculate_direction(coords1, coords2):
    x_change = coords2[0] - coords1[0]
    z_change = coords2[1] - coords1[1]

    if x_change >= 0 and z_change >= 0:
        return "southeast"
    elif x_change >= 0 and z_change < 0:
        return "southwest"
    elif x_change < 0 and z_change >= 0:
        return "northeast"
    else:
        return "northwest"

def calculate_new_coordinates(coords, slope, direction, distance, significant_coordinate):
    if direction == "southeast":
        sign_x = 1
        sign_z = 1
    elif direction == "southwest":
        sign_x = 1
        sign_z = -1
    elif direction == "northeast":
        sign_x = -1
        sign_z = 1
    else:
        sign_x = -1
        sign_z = -1
    
    if slope <= 2:
        dist_significant = distance * 0.7 * sign_x
        dist_nonsignificant = distance * 0.3 * sign_z
    elif slope <= 4:
        dist_significant = distance * 0.8 * sign_x
        dist_nonsignificant = distance * 0.2 * sign_z
    elif slope <= 8:
        dist_significant = distance * 0.87 * sign_x
        dist_nonsignificant = distance * 0.12 * sign_z
    elif slope <= 16:
        dist_significant = distance * 0.95 * sign_x
        dist_nonsignificant = distance * 0.05 * sign_z
    else:
        dist_significant = distance * sign_x
        dist_nonsignificant = 0

    if significant_coordinate == "x":
        new_coords = (coords[0] + dist_significant, coords[1] + dist_nonsignificant)
    else:
        new_coords = (coords[0] + dist_nonsignificant, coords[1] + dist_significant)
    
    adjusted_coords = (int(new_coords[0] / 16) * 16 + 4 * (1 if new_coords[0] > 0 else -1),
                       int(new_coords[1] / 16) * 16 + 4 * (1 if new_coords[1] > 0 else -1))
    
    if new_coords[0] < 0:
        adjusted_coords = (adjusted_coords[0] - 4, adjusted_coords[1])
    
    if new_coords[1] < 0 and significant_coordinate == "z" and direction in ["southeast", "northeast"]:
        adjusted_coords = (adjusted_coords[0], adjusted_coords[1] + 4)
    
    return adjusted_coords

def main():
    offset = float(input("Enter the offset: "))
    distance = 3636 / offset
    
    x1 = float(input("Enter the x coordinate of the first point: "))
    z1 = float(input("Enter the z coordinate of the first point: "))
    coords1 = (x1, z1)
    
    x2 = float(input("Enter the x coordinate of the second point: "))
    z2 = float(input("Enter the z coordinate of the second point: "))
    coords2 = (x2, z2)
    
    slope = (z2 - z1) / (x2 - x1)
    
    direction = calculate_direction(coords1, coords2)
    
    if abs(x2 - x1) > abs(z2 - z1):
        significant_coordinate = "x"
    else:
        significant_coordinate = "z"
    
    new_coords = calculate_new_coordinates(coords1, slope, direction, distance, significant_coordinate)
    
    nether_coords = (new_coords[0] / 8, new_coords[1] / 8)
    
    print("Stronghold Coordinates:", new_coords)
    print("Nether Coordinates:", nether_coords)

if __name__ == "__main__":
    main()

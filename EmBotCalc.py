def get_direction(x1, z1, x2, z2):
    return ("south" if x2 - x1 >= 0 else "north") + ("east" if z2 - z1 >= 0 else "west")

def calculate_coords(x, z, a, direction, axis):
    sx, sz = (1, 1) if direction == "south" else (-1, -1)
    ds = a * (0.35 if a <= 2 else 0.4 if a <= 4 else 0.435 if a <= 8 else 0.475 if a <= 16 else 1)
    df = 0.3 * (1 if a < 2 else 0)
    nx = x + ds if axis == "x" else x + df
    nz = z + ds if axis == "z" else z + df
    nx = (nx + 4) if nx < 0 else nx
    return nx, nz

def main():
    o, x1, z1, x2, z2 = map(float, input().split())
    a = abs(z2 - z1) / abs(x2 - x1)
    direction = get_direction(x1, z1, x2, z2)
    axis = "x" if abs(x2 - x1) > abs(z2 - z1) else "z"
    d, o = calculate_coords(x1, z1, a, direction, axis)
    d /= 8

    print(f"Stronghold Coordinates: ({d}, {o})")
    print(f"Nether Coordinates: ({d / 8}, {o / 8})")

if __name__ == "__main__":
    main()

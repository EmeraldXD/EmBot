document.addEventListener("DOMContentLoaded", function () {
  const calculateButton = document.getElementById("calculate-button");
  calculateButton.addEventListener("click", function () {
    const offset = parseFloat(document.getElementById("offset").value);
    const x1 = parseFloat(document.getElementById("x1").value);
    const z1 = parseFloat(document.getElementById("z1").value);
    const x2 = parseFloat(document.getElementById("x2").value);
    const z2 = parseFloat(document.getElementById("z2").value);

    const distance = 3636 / offset;
    const slope = (z2 - z1) / (x2 - x1);
    const direction = calculateDirection(x1, z1, x2, z2);
    const significantCoordinate =
      Math.abs(x2 - x1) > Math.abs(z2 - z1) ? "x" : "z";
    const newCoords = calculateNewCoordinates(
      x2,
      z2,
      slope,
      direction,
      distance,
      significantCoordinate,
      x1,
      x2,
      z1,
      z2
    );

    const strongholdCoordinates = `Stronghold Coordinates: (${newCoords.x}, ${newCoords.z})`;
    const netherCoordinates = `Nether Coordinates: (${newCoords.netherX}, ${newCoords.netherZ})`;

    const strongholdParagraph = document.getElementById(
      "stronghold-coordinates"
    );
    strongholdParagraph.textContent = strongholdCoordinates;

    const netherParagraph = document.getElementById("nether-coordinates");
    netherParagraph.textContent = netherCoordinates;
  });
});
document.addEventListener("DOMContentLoaded", function () {
  // ... Your existing code ...

  const clearButton = document.getElementById("clear-button");
  clearButton.addEventListener("click", function () {
    document.getElementById("offset").value = "";
    document.getElementById("x1").value = "";
    document.getElementById("z1").value = "";
    document.getElementById("x2").value = "";
    document.getElementById("z2").value = "";

    document.getElementById("stronghold-coordinates").textContent = "";
    document.getElementById("nether-coordinates").textContent = "";
  
  });
});

function calculateDirection(x1, z1, x2, z2) {
  const xChange = x2 - x1;
  const zChange = z2 - z1;

  if (xChange >= 0 && zChange >= 0) {
    return "southeast";
  } else if (xChange >= 0 && zChange < 0) {
    return "southwest";
  } else if (xChange < 0 && zChange >= 0) {
    return "northeast";
  } else {
    return "northwest";
  }
}

function calculateNewCoordinates(
  x,
  z,
  slope,
  direction,
  distance,
  significantCoordinate,
  x1,
  x2,
  z1,
  z2
) {
  const sign = direction === "southeast" || direction === "northeast" ? 1 : -1;

  let distSignificant, distNonSignificant;
  if (slope <= 2) {
    distSignificant = distance * 0.75 * sign;
    distNonSignificant = distance * 0.3 * sign;
  } else if (slope <= 4) {
    distSignificant = distance * 0.85 * sign;
    distNonSignificant = distance * 0.2 * sign;
  } else if (slope <= 8) {
    distSignificant = distance * 0.9 * sign;
    distNonSignificant = distance * 0.1 * sign;
  } else if (slope <= 16) {
    distSignificant = distance * 0.95 * sign;
    distNonSignificant = distance * 0.05 * sign;
  } else {
    distSignificant = distance * sign;
    distNonSignificant = distance * 0.05;
  }

  let adjustedX =
    x + (significantCoordinate === "x" ? distSignificant : distNonSignificant);
  let adjustedZ =
    z + (significantCoordinate === "z" ? distSignificant : distNonSignificant);

  adjustedX = Math.floor(adjustedX / 16) * 16 + 4;
  adjustedZ = Math.floor(adjustedZ / 16) * 16 + 4;

  if (adjustedX < 0) {
    adjustedX -= 4;
  }
  if (adjustedZ < 0) {
    adjustedZ -= 4;
  }
  if (
    adjustedZ < 0 &&
    significantCoordinate === "z" &&
    (direction === "southeast" || direction === "northeast")
  ) {
    adjustedZ += 4;
  }

  const netherX = adjustedX / 8;
  const netherZ = adjustedZ / 8;

  return { x: adjustedX, z: adjustedZ, netherX: netherX, netherZ: netherZ };
}

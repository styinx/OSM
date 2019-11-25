document.addEventListener("DOMContentLoaded", function () {

    new QWebChannel(qt.webChannelTransport, function (channel) {
        window.bridge = channel.objects.UIBridge;
        setMapBounds();
    });
});

let attribution = '';
let token = 'pk.eyJ1IjoibWFwYm94IiwiYSI6ImNpejY4NXVycTA2emYycXBndHRqcmZ3N3gifQ.rJcFIG214AriISLbB6B5aw';
let map = L.map('map').setView([48.745158, 9.106606], 15);
let popup = L.popup();

L.tileLayer('https://api.tiles.mapbox.com/v4/{id}/{z}/{x}/{y}.png?access_token={token}', {
    maxZoom: 20,
    attribution: '',
    id: 'mapbox.streets',
    token: token
}).addTo(map);

map.on("click", onMapClick);

function onMapClick(e) {
    popup.setLatLng(e.latlng)
        .setContent("Clicked at " + e.latlng.toString())
        .addTo(map);

    setMapBounds();
}

// JS -> C++

function setMapBounds() {
    let bounds = map.getBounds();
    let sw = bounds["_southWest"];
    let ne = bounds["_northEast"];

    bridge.setMapBounds(ne.lat, ne.lng, sw.lat, sw.lng);
}

// C++ -> JS

function showGraph(nodeList) {

    for (let index = 0; index < nodeList.length; ++index) {
        for (let node = 0; node < nodeList[index].length; ++node) {
            L.circle(nodeList[index][node], {
                radius: 1,
                color: 'rgba(255, 200, 0, 0.75)'
            }).addTo(map);
        }
        L.polyline(nodeList[index], {color: 'rgba(0, 100, 200, 0.25)'}).addTo(map);
    }
}

function addGeoJSON(lines) {
    L.geoJSON({
        type: "LineString",
        coordinates: lines
    }, {
        style: {
            color: "rgba(0, 150, 255, 0.75)",
            weight: 4
        }
    }).addTo(map);
}

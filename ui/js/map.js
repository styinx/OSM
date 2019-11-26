document.addEventListener("DOMContentLoaded", function () {

    new QWebChannel(qt.webChannelTransport, function (channel) {
        window.bridge = channel.objects.UIBridge;
        setMapBounds();
    });
});

let attribution = '';
let token = 'pk.eyJ1IjoibWFwYm94IiwiYSI6ImNpejY4NXVycTA2emYycXBndHRqcmZ3N3gifQ.rJcFIG214AriISLbB6B5aw';
let map = L.map('map').setView([48.745158, 9.106606], 15);
var routeLayer = L.layerGroup([]).addTo(map);
var graphLayer = L.layerGroup([]).addTo(map);
let popup = L.popup();

L.tileLayer('https://api.tiles.mapbox.com/v4/{id}/{z}/{x}/{y}.png?access_token={token}', {
    maxZoom: 20,
    attribution: '',
    id: 'mapbox.streets',
    token: token
}).addTo(map);

map.on("click", onMapClick);
map.on("zoomend", onZoomEnd);
map.on("mouseup", onMouseUp);

function onMapClick(e) {
    popup.setLatLng(e.latlng)
        .setContent("What's here?<br> " + e.latlng.toString())
        .addTo(map);
}

function onZoomEnd(e) {
    setMapBounds();
}

function onMouseUp(e) {
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

function showGraph(graph) {
    if(map.getZoom() >= 10) {
        graphLayer.clearLayers();

        let nodeColor = 'rgba(255, 200, 0, 0.75)';
        let edgeColor = 'rgba(0, 100, 200, 0.25)';

        for (let index = 0; index < graph.length; ++index) {
            for (let edge = 0; edge < graph[index].length; ++edge) {

                if (graph[index].length >= 1) {
                    L.circle(graph[index][0], {
                        radius: 1,
                        color: nodeColor
                    }).addTo(graphLayer);
                }

                if (graph[index].length === 2) {
                    L.circle(graph[index][1], {
                        radius: 1,
                        color: nodeColor
                    }).addTo(graphLayer);

                    L.polyline(graph[index], {color: edgeColor}).addTo(graphLayer);
                }
            }
        }
    }
}

function showRoute(lines) {
    routeLayer.resetLayer();

    routeLayer.addLayer(L.geoJSON({
        type: "LineString",
        coordinates: lines
    }, {
        style: {
            color: "rgba(0, 150, 255, 0.75)",
            weight: 4
        }
    }));
}

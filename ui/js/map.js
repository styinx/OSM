class UIBridge {
    constructor(bridge, map) {
        this.ui_bridge = bridge;
        this.map = map;

        this.map.l_map.on("click", this.onMapClick);
    }

    onMapClick(e) {
        let map = window.map;
        let bridge = window.bridge;

        let latlng = e.latlng.lat.toFixed(6).toString() + "," + e.latlng.lng.toFixed(6).toString();

        let start = "<button onclick='bridge.setStart(\"" + latlng + "\")'>Set start</button>";
        let stop = "<button onclick='bridge.setStop(\"" + latlng + "\")'>Set stop</button>";

        map.l_popup.setLatLng(e.latlng)
            .setContent(start + "&nbsp;" + stop)
            .addTo(map.l_map);
    }

    // JS -> C++

    onLoad() {
        this.ui_bridge.onLoad();
    }

    setMapBounds() {
        let bounds = this.map.l_map.getBounds();
        let sw = bounds["_southWest"];
        let ne = bounds["_northEast"];

        this.ui_bridge.setMapBounds(ne.lat, ne.lng, sw.lat, sw.lng);
    }

    setStart(latlon) {
        this.ui_bridge.setStart(latlon);
    }

    setStop(latlon) {
        this.ui_bridge.setStop(latlon);
    }

    // C++ -> JS

    setView(lat, lon) {
        this.map.setView(lat, lon);
    }

    setGraph(graph) {
        this.map.setGraph(graph);
    }

    showGraph(bool) {
        this.map.showGraph(bool);
    }

    showRoute(route) {
        this.map.showRoute(route);
    }
}

class Map {
    constructor() {
        this.l_map = L.map('map').setView([0, 0], 0);
        this.l_popup = L.popup();

        this.routeLayer = L.layerGroup([]).addTo(this.l_map);
        this.graphLayer = L.layerGroup([]).addTo(this.l_map);

        this.showNetwork = false;
        this.graphData = [];

        this.style = {
            'nodeColor': 'rgba(255, 255, 0, 0.25)',
            'edgeColor': 'rgba(255, 50, 0, 0.25)',
            'routeColor': 'rgba(0, 150, 255, 0.75)'
        };

        let token = 'pk.eyJ1IjoibWFwYm94IiwiYSI6ImNpejY4NXVycTA2emYycXBndHRqcmZ3N3gifQ.rJcFIG214AriISLbB6B5aw';
        L.tileLayer('https://api.tiles.mapbox.com/v4/{id}/{z}/{x}/{y}.png?access_token={token}', {
            maxZoom: 20,
            attribution: '',
            id: 'mapbox.streets',
            token: token
        }).addTo(this.l_map);
    }

    setView(lat, lon) {
        this.l_map.setView([lat, lon], this.l_map.getZoom())
    }

    setGraph(graph) {
        this.graphData = graph
    }

    showGraph(show) {
        this.showNetwork = show;

        if (!this.showNetwork) {
            this.graphLayer.clearLayers();
        } else {
            for (let index = 0; index < this.graphData.length; ++index) {
                for (let edge = 0; edge < this.graphData[index].length; ++edge) {

                    // if (graph[index].length >= 1) {
                    //     L.circle(graph[index][0], {
                    //         radius: 1,
                    //         color: this.style['nodeColor'],
                    //         interactive: false
                    //     }).addTo(graphLayer);
                    // }

                    if (this.graphData[index].length === 2) {
                        // L.circle(graph[index][1], {
                        //     radius: 1,
                        //     color: this.style['nodeColor'],
                        // }).addTo(graphLayer);

                        L.polyline(this.graphData[index], {
                            color: this.style['edgeColor'],
                            interactive: false
                        }).addTo(this.graphLayer);
                    }
                }
            }
        }
    }

    showRoute(lines) {
        this.routeLayer.clearLayers();

        this.routeLayer.addLayer(L.geoJSON({
            type: "LineString",
            coordinates: lines
        }, {
            style: {
                color: this.style['routeColor'],
                weight: 4
            }
        }));
    }
}

document.addEventListener("DOMContentLoaded", function () {

    new QWebChannel(qt.webChannelTransport, function (channel) {
        window.map = new Map();
        window.bridge = new UIBridge(channel.objects.UIBridge, map);

        bridge.onLoad();
        bridge.setMapBounds();
    });
});

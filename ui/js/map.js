var style = {
    'nodeColor': 'rgba(255, 255, 0, 0.25)',
    'edgeColor': 'rgba(255, 50, 0, 0.25)',
    'routeColor': 'rgba(0, 150, 255, 0.75)'
};

class UIMap {
    constructor(cpp_ui_map, ll_map) {
        this.cpp_ui_map = cpp_ui_map;
        this.map = ll_map;

        this.map.l_map.on("click", this.onMapClick);
    }

    onMapClick(e) {
        let map = window.map;
        let ui_map = window.ui_map;

        let latlng = e.latlng.lat.toFixed(6).toString() + "," + e.latlng.lng.toFixed(6).toString();

        let start = "<button onclick='ui_map.setStart(\"" + latlng + "\")'>Set start</button>";
        let stop = "<button onclick='ui_map.setStop(\"" + latlng + "\")'>Set stop</button>";

        map.l_popup.setLatLng(e.latlng)
            .setContent(start + "&nbsp;" + stop)
            .addTo(map.l_map);
    }

    // JS -> C++

    onLoad() {
        this.cpp_ui_map.onLoad();
    }

    // setMapBounds() {
    //     let bounds = this.map.l_map.getBounds();
    //     let sw = bounds["_southWest"];
    //     let ne = bounds["_northEast"];
    //
    //     this.ui_bridge.setMapBounds(ne.lat, ne.lng, sw.lat, sw.lng);
    // }

    setStart(latlon) {
        this.cpp_ui_map.setStart(latlon);
    }

    setStop(latlon) {
        this.cpp_ui_map.setStop(latlon);
    }

    // C++ -> JS

    setView(lat, lon, zoom) {
        this.map.setView(lat, lon, zoom);
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

class UIGraph {
    constructor(cpp_ui_graph, map) {
        this.cpp_ui_graph = cpp_ui_graph;
        this.map = map;
        this.l_renderer = L.canvas({padding: 0.5});

        this.graphs = {"motorway": []};
        this.layers = {"motorway": L.layerGroup([])};
    }

    computeGraph(tpye) {

    }

    show() {
        let zoom = this.map.l_map.getZoom();

        console.log(JSON.stringify(this.cpp_ui_graph.motorway));
        this.graphs["motorway"] = JSON.parse(this.cpp_ui_graph.motorway );

        L.polyline(this.graphs["motorway"], {
            renderer: this.l_renderer,
            color: style['edgeColor'],
            interactive: false
        }).addTo(this.map.l_map);

        this.motorway.addTo(this.map.l_map);

        if (zoom > 15) {

        }
    }
}

class Map {
    constructor() {
        this.l_map = L.map('map').setView([0, 0], 10);

        this.l_popup = L.popup();

        this.routeLayer = L.layerGroup([]);
        this.graphLayer = L.layerGroup([]);

        this.showNetwork = false;

        let token = 'pk.eyJ1IjoibWFwYm94IiwiYSI6ImNpejY4NXVycTA2emYycXBndHRqcmZ3N3gifQ.rJcFIG214AriISLbB6B5aw';
        L.tileLayer('https://api.tiles.mapbox.com/v4/{id}/{z}/{x}/{y}.png?access_token={token}', {
            maxZoom: 20,
            attribution: '',
            id: 'mapbox.streets',
            token: token
        }).addTo(this.l_map);
    }

    setView(lat, lon, zoom=-1) {
        let _zoom = zoom === -1 ? this.l_map.getZoom() : zoom;

        this.l_map.setView([lat, lon], _zoom);
    }

    showGraph(show) {
        this.showNetwork = show;

        if (!this.showNetwork) {
            this.l_map.removeLayer(this.graphLayer);
        } else {
            this.graphLayer.addTo(this.l_map);
        }
    }

    showRoute(lines) {
        this.routeLayer.clearLayers();

        this.routeLayer.addLayer(L.geoJSON({
            type: "LineString",
            coordinates: lines
        }, {
            style: {
                color: style['routeColor'],
                weight: 4
            }
        })).addTo(this.l_map);
    }
}

document.addEventListener("DOMContentLoaded", function () {

    new QWebChannel(qt.webChannelTransport, function (channel) {
        window.map = new Map();

        window.ui_graph = new UIGraph(channel.objects.UIGraph, map);
        window.ui_map = new UIMap(channel.objects.UIMap, map);

        window.ui_map.onLoad();
    });
});

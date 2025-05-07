from opcua import Client, ua

class OPCUAClient:
    def __init__(self, server_url):
        self.client = Client(server_url)

    def connect(self):
        try:
            self.client.connect()
            print("Connected to OPC UA Server")
            return 1
        except Exception as e:
            print(f"Failed to connect: {e}")
            return -1

    def disconnect(self):
        self.client.disconnect()
        print("Disconnected from OPC UA Server")

    def read_node(self, node_id):
        try:
            node = self.client.get_node(node_id)
            value = node.get_value()
            print(f"Node: {node_id}, Value: {value}")
            return str(value)
        except Exception as e:
            print(f"Failed to read node: {e}")
            return None

    def write_node(self, node_id, value):
        try:
            node = self.client.get_node(node_id)
            node.set_value(ua.Variant(value, ua.VariantType.String))
            print(f"Node: {node_id}, New Value: {value}")
        except Exception as e:
            print(f"Failed to write node: {e}")

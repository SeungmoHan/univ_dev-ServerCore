import argparse
import jinja2
import ProtoParser


def main():

    arg_parser = argparse.ArgumentParser(description = 'PacketGenerator')
    arg_parser.add_argument('--path', type=str, default='C:/Users/user/Desktop/Education/Portfolio/GameServer/Server/Common/Protobuf/bin/Protocol.proto', help='proto path')
    arg_parser.add_argument('--output', type=str, default='TestPacketHandler', help='output file')
    arg_parser.add_argument('--recv', type=str, default='CS_', help='recv convention')
    arg_parser.add_argument('--send', type=str, default='SC_', help='send convention')
    args = arg_parser.parse_args()

    parser = ProtoParser.ProtoParser(1000, args.recv, args.send)
    parser.parse_proto(args.path)

    #jinja2
    file_loader = jinja2.FileSystemLoader("Template")
    env = jinja2.Environment(loader = file_loader)

    template = env.get_template('PacketHandler.template')
    output = template.render(parser=parser, output=args.output)



    f = open(args.output+'.h', 'w+')
    f.write(output)
    f.close()

    print(output)

    
    return


if __name__ == '__main__':
    main()
